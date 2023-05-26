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
	BIGNUM *d = BN_new(); 
	BIGNUM *S = BN_new(); 
	BIGNUM *e = BN_new(); 
	BIGNUM *M = BN_new(); 
	BIGNUM *M2 = BN_new(); 
	BIGNUM *n = BN_new(); 
	

	//Initialize the variables with their values 
	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
	BN_hex2bn(&e, "010001");
	BN_hex2bn(&M, "48656c6c6f20496d204b617421"); //Hello Im Kat!
	BN_hex2bn(&M2, "48656c6c6f20496d204b617321"); //Hello Im Kas!
	
	printBN("The original message in hex is: ", M);

	//Calculate the signature S
	BN_mod_exp(S, M, d, n, ctx);
	printBN("S: ", S);

	BN_mod_exp(M, S, e, n, ctx);
	printBN("Verify Signature: ", M);	

	printBN("The edited message in hex is: ", M2);

	//Calculate the signature S
	BN_mod_exp(S, M2, d, n, ctx);
	printBN("S: ", S);

	BN_mod_exp(M, S, e, n, ctx);
	printBN("Verify Signature: ", M2);
	return 0;
}