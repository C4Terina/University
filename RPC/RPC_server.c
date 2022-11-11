#include "RPC.h"

avg *rpc_avg_1_svc(input *argp, struct svc_req *rqstp){
	static avg  result;
	int i, sum = 0;

	for(i = 0; i < argp->Y.Y_len; i++)
		sum += argp->Y.Y_val[i]; // Add to sum

	result.avgrs = (float)sum / (float)argp->Y.Y_len; // Save to the struct the average
	return &result;
}

min_max *rpc_mm_1_svc(input *argp, struct svc_req *rqstp){
	static min_max  result;
	int i;

	result.mm.mm_len = 2; // Set length of the array.
	result.mm.mm_val = (int *) calloc (result.mm.mm_len, sizeof(int)); // Allocate the space for the array
	result.mm.mm_val[0] = argp->Y.Y_val[0]; // Set Min to first pos of the array
	result.mm.mm_val[1] = argp->Y.Y_val[0]; // Set Max to first pos of the array

	for(i = 1; i < argp->Y.Y_len; i++){
		if(result.mm.mm_val[0] >= argp->Y.Y_val[i]) // Max
			result.mm.mm_val[0] = argp->Y.Y_val[i];

		if(result.mm.mm_val[1] < argp->Y.Y_val[i]) // Min
			result.mm.mm_val[1] = argp->Y.Y_val[i];
	}

	return &result;
}

mult *rpc_mult_1_svc(input *argp, struct svc_req *rqstp){
	static mult  result;
	int i;

	result.mulrs.mulrs_len = argp->Y.Y_len; // Set length of array
	result.mulrs.mulrs_val = (float *) calloc(argp->Y.Y_len, sizeof(float)); // Allocate space

	for(i = 0; i < argp->Y.Y_len; i++)
		result.mulrs.mulrs_val[i] = argp->a * argp->Y.Y_val[i]; //Calculate a * Y

	return &result;
}
