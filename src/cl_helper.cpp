#include "cl_helper.h"

cl::Platform mf_clh::getPlatform() {
	/* Returns the first platform found. */
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);

	if (all_platforms.size() == 0) {
		std::cout << "No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	return all_platforms[0];
}

cl::Device mf_clh::getDevice(cl::Platform platform, int i, bool display) {
	/* Returns the deviced specified by the index i on platform.
		* If display is true, then all of the platforms are listed.
		*/
	std::vector<cl::Device> all_devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << "No devices found. Check OpenCL installation!\n";
		exit(1);
	}

	if (display) {
		for (int j = 0; j < all_devices.size(); j++)
			printf("Device %d: %s\n", j, all_devices[j].getInfo<CL_DEVICE_NAME>().c_str());
	}
	return all_devices[i];
}

char* mf_clh::readSource(const char *sourceFilename) {
	FILE *fp;
	int err;
	int size;
	char *source;

	fp = fopen(sourceFilename, "rb");

	if (fp == NULL) {
		printf("Could not open kernel file: %s\n", sourceFilename);
		//exit(-1);
	}

	err = fseek(fp, 0, SEEK_END);
	if (err != 0) {
		printf("Error seeking to end of file\n");
		//exit(-1);
	}

	size = ftell(fp);
	if (size < 0) {
		printf("Error getting file position\n");
		// exit(-1);
	}

	err = fseek(fp, 0, SEEK_SET);
	if (err != 0) {
		printf("Error seeking to start of file\n");
		//exit(-1);
	}

	source = (char*)malloc(size + 1);
	if (source == NULL) {
		printf("Error allocating %d bytes for the program source\n", size + 1);
		//exit(-1);
	}

	err = fread(source, 1, size, fp);
	if (err != size) {
		printf("only read %d bytes\n", err);
		// exit(0);
	}

	source[size] = '\0';

	return source;
}