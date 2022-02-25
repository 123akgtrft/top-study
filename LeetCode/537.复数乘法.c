void turn(char*num1,int*real1,int*imag1){
    char*token=strtok(num1,"+");
    *real1=atoi(token);
    token=strtok(NULL,"i");
    *imag1=atoi(token);
}
char * complexNumberMultiply(char * num1, char * num2){
    int real1,real2,imag1,imag2;
    turn(num1,&real1,&imag1);
    turn(num2,&real2,&imag2);
    char*res=(char*)malloc(sizeof(char)*14);
    sprintf(res,"%d+%di",real1*real2-imag1*imag2,real1*imag2+real2*imag1);
    return res;
}
