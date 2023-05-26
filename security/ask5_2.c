#include <stdio.h> 
#include <openssl/bn.h> 
#define NBITS 256 

void printBN(char *msg, BIGNUM * a){ 
	char * number_str = BN_bn2hex(a); 
	printf("%s %s\n", msg, number_str); 
	OPENSSL_free(number_str); 
}

int main(){

	//Variables 
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *S = BN_new(); 
	BIGNUM *e = BN_new(); 
	BIGNUM *M = BN_new(); 
	BIGNUM *n = BN_new(); 
	BIGNUM *V = BN_new();
	

	//Initialize the variables with their values 
	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&e, "010001");
	BN_hex2bn(&M, "506c65617365207472616e73666572206d652024323030302e416c6963652e"); //Please transfer me $2000.Alice.
	BN_hex2bn(&S, "DB3F7CDB93483FC1E70E4EACA650E3C6505A3E5F49EA6EDF3E95E9A7C6C7A320"); 
	
	printBN("The original message in hex is: ", M);

	BN_mod_exp(V, S, e, n, ctx);
	printBN("Verify Signature: ", V);

	if(BN_cmp(V, M)) //compare the message and the signature. If true then it's ALice's else it isn't
		printf("The signature is from Alice\n");
	else
		printf("The signature isn't from Alice\n");	

	return 0;
}