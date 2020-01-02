#include "texdiv.h"
#include "kullack_leibller.h"

#define MC_SAMPLES 1e6

namespace po = boost::program_options;

float *load_models(const std::string &filepath, int &M, int &D) {
    std::ifstream fs;
    std::string line;
    int i = 0;
    float *models = nullptr;

    try {
        fs.open(filepath);
        // Get the first line which contains basic information about the models structure
        getline(fs, line);
        std::string svalue;
        std::istringstream ls(line);

        D = 0;
        M = 0;
        while (getline(ls, svalue, ','))
            D++;

        models = (float *) malloc(sizeof(float) * D);
        fs.seekg(0);
        while (getline(fs, line)) {
            std::istringstream ls(line);
            while (getline(ls, svalue, ',')) {
                models[i++] = std::stod(svalue);
            }
            M++;
            models = (float *) realloc(models, sizeof(float) * D * (M+1));
        }

    } catch (std::ifstream::failure &ex) {
        std::cerr << "The models file could not be opened" << "\n";
    }

    return models;
}

double csd_weibull(float *models, size_t i, size_t j, size_t M, bool use_mci = false, size_t N = 1e6) {
    float a1, b1, a2, b2, div = 0.0f, I1, I2;

    /**
     * The weibull model is coded as follows {a00 b00 a01 b01 a02 b02 ... aij bij ... aLJ bLJ}
     * with i the scale index and j the subband index.
     */
    for (size_t k = 0; k < M - 1; k += 2) {
        a1 = models[i + k * M];
        b1 = models[i + (k + 1) * M];
        a2 = models[j + k * M];
        b2 = models[j + (k + 1) * M];
        I1 = powf(a1 / a2, b2) * (tgammaf((b2 + 1) / b1) / tgammaf(1 / b1)) - 1 / b1;
        I2 = (b2 / a2) * (powf(2, (1 / b2 - 2))) * tgammaf(2 - 1 / b2);

        div += I1 + I2;
    }

    return div;
}

float kld_weibull(const float *models, size_t i, size_t j, size_t D, bool use_mci = false, size_t N = 1e6) {
    float a1, b1, a2, b2, div = 0, I1, I2, lambda = 0.577f;

    /**
     * The weibull model is coded as follows {a00 b00 a01 b01 a02 b02 ... aij bij ... aLJ bLJ}
     * with i the scale index and j the subband index.
     */
    for (size_t k = 0; k < D - 1; k += 2) {
        a1 = models[i + k * D];
        b1 = models[i + (k + 1) * D];
        a2 = models[j + k * D];
        b2 = models[j + (k + 1) * D];
        div += powf(b1 / b2, a2) * tgammaf(a2 / a1 + 1) + logf(a1 / (powf(b1, a1)))
               - logf(a2 / powf(b2, a2)) + logf(b1) * a1 - logf(b1) * a2 + lambda * a2 / a1 - lambda - 1;
    }

    return div;
}

/* The gateway function */
int main(int argc, char *argv[]) {
    std::string modelsFilePath;
    float *divs = nullptr, *models; /* output divergences matrix */
    int D = 0, M = 0, N = 1000000, i, j;
    bool use_mci = false, use_gpu = false;
    DivergenceType div_type;
    po::options_description desc("All options");

    desc.add_options()
            ("models", po::value<std::string>(), "Models file path")
            ("mci", po::value<bool>(), "Use Monte Carlo integration")
            ("gpu", po::value<bool>(), "Use GPU acceleration")
            ("type", po::value<std::string>(), "Type of divergence (csd or kld)");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (!vm.count("models")) {
        std::cerr << "You have to define models file" << "\n";
        exit(1);
    } else {
        modelsFilePath = vm["models"].as<std::string>();
        models = load_models(modelsFilePath, M, D);
    }

    if (vm.count("type")) {
        if (vm["type"].as<std::string>() == "csd") {
            div_type = DivergenceType::CSD;
        } else {
            div_type = DivergenceType::KLD;
        }
    }

    /* Get options */
    use_gpu = (vm.count("gpu") && vm["gpu"].as<bool>());
    use_mci = (vm.count("mci") && vm["mci"].as<bool>());

    texdiv::KullbackLeibller divergence("weibull", M, D);
    divergence.init();
    divs = divergence.compute(models);

    free(models);

    std::cout << "Saving data...\n";

    if (divs) {
        std::ofstream out("data/divs.csv");
        for (i = 0; i < M; i++) {
            for (j = 0; j < M; j++) {
                out << divs[i * M + j] << ',';
            }
            out << '\n';
        }
        out.close();
    }

    free(divs);
}
