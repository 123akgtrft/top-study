bool isMatch(char * s, char * p){
    if(!*p)//p空了
        return !*s;
    bool match=*s&&(*s==*p||*p=='.');
    if(*(p+1)=='*'){
        return isMatch(s,p+2)||(match&&isMatch(++s,p));
    
    }return match&&isMatch(++s,++p);
}
