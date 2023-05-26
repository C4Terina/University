#include <stdio.h> 
#include <openssl/bn.h> 
#define NBITS 256 

void printBN(char *msg, BIGNUM * a){ 
	char * number_str = BN_bn2hex(a); 
	printf("%s %s\n", msg, number_str); 
	OPENSSL_free(number_str); 
}

int main(){

	//Variables we will use to encode the message 
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *d = BN_new(); 
	BIGNUM *C = BN_new(); 
	BIGNUM *e = BN_new(); 
	BIGNUM *M = BN_new(); 
	BIGNUM *n = BN_new(); 

	//Initialize the variables with their values 
	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
	BN_hex2bn(&e, "010001");
	BN_hex2bn(&C, "CAF7D72776AFEFBAC8269E1A8B76CE44A3B28015CA9A54E22C239EF38FCFAFFA"); //The message in hex 

	//Calculate mod_exp of C to find the decrypted message
	BN_mod_exp(M, C, d, n, ctx);
	printBN("M = ", M);

	return 0;
}