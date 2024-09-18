#include<stdio.h>
#include<string.h>
int main(){
	char sub[100];
	char plain[100];
	char cipher[100];
	char alphabet[26];
	char c;
	int index;
	printf("Enter susbstitution key: ");
	scanf("%s",sub);
	printf("Enter plain text: ");
	scanf("%s",plain);
	for(int i=0;i<26;i++){
		alphabet[i]='A'+i;
	}
	for(int i=0;i<strlen(plain);i++){
		c=plain[i];
		if(c>='a'&&c<='z'){
			index=c-'a';
			cipher[i]=sub[index];
		}
	}
	printf("Cipher text : %s",cipher);
	return 0;
}
