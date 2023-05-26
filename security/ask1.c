#include <stdio.h> 
#include <openssl/bn.h> 
#define NBITS 256 

void printBN(char *msg, BIGNUM * a){ 
	/* Use BN_bn2hex(a) for hex string 
	 Use BN_bn2dec(a) for decimal string */ 
	char * number_str = BN_bn2hex(a); 
	printf("%s %s\n", msg, number_str); 
	OPENSSL_free(number_str); 
}

int main(){
	
	
	BN_CTX *ctx = BN_CTX_new(); //ctx structure
	BIGNUM *p = BN_new(); //the p variable
	BIGNUM *a = BN_new(); //to hold "1"
	BIGNUM *q = BN_new(); //the q variable
	BIGNUM *e = BN_new(); //the e variable
	BIGNUM *d = BN_new(); //the d variable
	BIGNUM *res = BN_new(); 
	BIGNUM *res2 = BN_new(); 
	BIGNUM *res3 = BN_new();
	BIGNUM *res4 = BN_new(); 
	BIGNUM *res5 = BN_new(); 
	
	BN_hex2bn(&p, "953AAB9B3F23ED593FBDC690CA10E703"); 
	BN_hex2bn(&q, "C34EFC7C4C2369164E953553CDF94945");
	BN_hex2bn(&e, "0D88C3");
	BN_dec2bn(&a, "1");
	
	//Calculate p-1
	BN_sub(res, p, a);
	printBN("p - 1: ", res);
	
	//Calculate q-1
	BN_sub(res2, q, a); 
	printBN("q - 1: ", res2);
	
	//Calculate (p-1)*(q-1)
	BN_mul(res3, res, res2, ctx);
	printBN("(p-1)*(q-1): ", res3);


	//Calculate mod inverse and print d
	BN_mod_inverse(d, e, res3, ctx);
	
	printBN("d: ", d);

	return 0;


}
