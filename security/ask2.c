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

	//Variables we will use to encode the message 
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *d = BN_new(); 
	BIGNUM *C = BN_new(); 
	BIGNUM *e = BN_new(); 
	BIGNUM *M = BN_new(); 
	BIGNUM *n = BN_new(); 
	BIGNUM *p = BN_new();
	BIGNUM *q = BN_new();

	//Initialize the variables with their values from drasthriothta 1 
	BN_hex2bn(&p, "953AAB9B3F23ED593FBDC690CA10E703"); 
	BN_hex2bn(&q, "C34EFC7C4C2369164E953553CDF94945");
	BN_hex2bn(&d, "63F67E805D8DEB0B4182C57C3DC24F3C1350CF182E8ABF85FD24062A3BC7F2EB");
	BN_hex2bn(&e, "0D88C3");
	BN_hex2bn(&M, "4b61746572696e6120506170616368726973746f646f756c6f75"); //The message in hex 

	
	//Calculate n = q*p 
	BN_mul(n, q, p, ctx);
	
	//Calculate mod_exp of M to find encoded message and C to find the decrypted 
	BN_mod_exp(C, M, e, n, ctx);
	printBN("C = ", C);
	BN_mod_exp(M, C, d, n, ctx);
	printBN("M = ", M);

	return 0;
}