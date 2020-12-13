void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

//esta função não foi criada por mim. vi que não tinha a func itoa no meu system, 
//então peguei do stack overflow (preguiça de implementar), por Keith Thompson. converte um inteiro n em string
 void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  
         n = -n;          
     i = 0;
     do {  
         s[i++] = n % 10 + '0';
     } while ((n /= 10) > 0); 
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}
