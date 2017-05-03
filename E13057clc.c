
#include <stdio.h>

long string2int(char *);
float string2float(char *);
void string2bin(char *);
void string2bin64(char *);
void string2hex(char *);
void string2hex16(char *);

void int2bin(int);
void int2hex();
int bin2int();
void bin2hex();
void bin2hex16();
void double2double(char *);
void double2bin(float);
void double2hex();
void bin2float();
void bin2double();
void float2bin(float);
void float2hex();
void hex2hex();
int hex2int();
void hex2bin();
void hex2bin64();
void hex2float();
void hex2double();

// global variables
int binaryArr[32];
int bin64Arr[64];
char hexArr[8];
char hexArr16[16];

int main(int argc, char** argv){

    int j;

    // Error-  Wrong number of arguments
    if(argc != 4){
        fprintf(stderr,"ERROR: The number of arguments is wrong.\n");
        fprintf(stderr,"Usage: ./clc -<input format> -<output format> <input>\n");
        return 1;
    }

    // Error - wrong input argument
    if(!(argv[1][1]=='B' || argv[1][1]=='H' || argv[1][1]=='I' || argv[1][1]=='F' || argv[1][1]=='D')){
        fprintf(stderr,"ERROR: The input argument is wrong.\n");
        fprintf(stderr,"Possible input arguments are -B, -H, -I, -F and -D.");
        return 1;
    }

    // Error - wrong input argument
    if(!(argv[2][1]=='B' || argv[2][1]=='H' || argv[2][1]=='I' || argv[2][1]=='F' || argv[2][1]=='D')){
        fprintf(stderr,"ERROR: The output argument is wrong.\n");
        fprintf(stderr,"Possible output arguments are -B, -H, -I, -F and -D.");
        return 1;
    }

    // Input type - Integer
    if(argv[1][1]=='I'){
        // check input format errors
        if(!((argv[3][0] == '-') || (argv[3][0]>=48 && argv[3][0]<=57))){
            fprintf(stderr,"ERROR: Input format error at location 0.\n");
            return 1;
        }

        while(argv[3][j+1]!='\0'){
            if(!(argv[3][j+1]>=48 && argv[3][j+1]<=57)){
                fprintf(stderr,"ERROR: Input format error at location %d.\n",j+1);
                return 1;
            }
            j++;
        }

        // check whether the input size is wrong
        if(string2int(argv[3])> 2147483647 || string2int(argv[3])< -2147483648){
            fprintf(stderr,"ERROR: The input size is wrong.\n");
            return 1;
        }

        // Integer --> Integer
        if(argv[2][1]=='I'){
            fprintf(stdout,"%ld\n",string2int(argv[3]));
        }
        // Integer --> Binary
        if(argv[2][1]=='B'){
            int2bin(string2int(argv[3]));
            for(j = 31 ; j>= 0; j--){
                fprintf(stdout,"%d",binaryArr[j]);
            }
            fprintf(stdout,"\n");
        }
        //  Integer --> Double
        if(argv[2][1]=='D'){
            fprintf(stderr,"ERROR: This conversion is not possible.\n");
            return 1;
        }
        // Integer --> Float
        if(argv[2][1]=='F'){
            fprintf(stdout,"%ld",string2int(argv[3]));
            fprintf(stdout,".00");
            fprintf(stdout,"\n");
        }
        // Integer --> Hexadecimal
        if(argv[2][1]=='H'){
            fprintf(stdout,"0x");
            int2bin(string2int(argv[3]));
            int2hex();
            for(j=7;j>=0; j--){
                fprintf(stdout,"%c",hexArr[j]);
            }
            fprintf(stdout,"\n");
        }
    }

    // Input Format - Binary
    if(argv[1][1]=='B'){

        int count=0;

        while(argv[3][j]!='\0'){  // count the number of bits in the input
           count++;
            j++;
        }
        if(argv[2][1]!='D'){
        if(count!=32){ // check the input size error
            fprintf(stderr,"ERROR: The input size is wrong.\n");
            return 1;
        }
        }
        else{
           if(count!=64){ // check the input size error
            fprintf(stderr,"ERROR: The input size is wrong.\n");
            return 1;
        }
        }

         for(j=0;j<count;j++){  // check input format error
            if(argv[3][j] != 48 && argv[3][j] != 49){
                fprintf(stderr,"ERROR: Input format error at location %d.\n",j);
                return 1;
            }
        }

        string2bin(argv[3]);

        // Binary --> Integer
        if(argv[2][1]=='I'){
            fprintf(stdout,"%d\n",bin2int());
        }
        // Binary --> Binary
        if(argv[2][1]=='B'){
            for(j = 0 ; j< count; j++){
                fprintf(stdout,"%d",binaryArr[j]);
            }
            fprintf(stdout,"\n");
        }
        // Binary --> Hexadecimal
        if(argv[2][1]=='H'){
            fprintf(stdout,"0x");
            bin2hex();
            for(j=7;j>=0; j--){
                fprintf(stdout,"%c",hexArr[j]);
            }
            fprintf(stdout,"\n");
        }
        // Binary --> Float
        if(argv[2][1]=='F'){
            bin2float();
        }
        // Binary --> Double
        if(argv[2][1]=='D'){
            if(count==64){ // check the input size error
                string2bin64(argv[3]);
                bin2double();
            }
            else{
                fprintf(stderr,"ERROR: The input size is wrong.\n");
                return 1;
            }
        }
    }

    // Input format - Float
    if(argv[1][1]=='F'){

        int count=0,k=0;
       // check input format error
        while(argv[3][j]!='\0'){
            if(!((argv[3][j]>=48 && argv[3][j]<=57) || (argv[3][j]=='.' )|| (argv[3][j] == '-'))){
                fprintf(stderr,"ERROR: Input format error at location %d.\n",j);
                return 1;
            }
            j++;
        }
        // check unwanted '.' in the input
        while(argv[3][k]!='\0'){
            if(argv[3][k]=='.'){
                ++count;
            }
            if(count>1){
                fprintf(stderr,"ERROR: Input format error at location %d.\n",k);
                return 1;
            }
            k++;
        }

        // Float --> Double
        if(argv[2][1]=='D'){
            fprintf(stderr,"ERROR: This conversion is not possible.\n");
            return 1;
        }
        // Float --> Integer
        if(argv[2][1]=='I'){

            int value = string2float(argv[3]);
            if(value > 2147483647 || value < -2147483648){
                fprintf(stderr,"ERROR: This conversion is not possible.\n");
                return 1;
            }
            else{
            fprintf(stderr,"WARNING: There is a possibility for a precision loss.");
            fprintf(stdout,"%d\n",value);
            }
        }
        // Float --> Binary
        if(argv[2][1]=='B'){
            float2bin(string2float(argv[3]));
            for(j=0;j<32;j++){
                fprintf(stdout,"%d",binaryArr[j]);
            }
            fprintf(stdout,"\n");
        }
         // Float --> Hexadecimal
        if(argv[2][1]=='H'){
            float2bin(string2float(argv[3]));
            float2hex();
        }

         // Float --> Float
        if(argv[2][1]=='F'){
            fprintf(stdout,"%.2f\n",string2float(argv[3]));
        }

    }

    // Input format - Double
     if(argv[1][1]=='D'){

         int count=0,k=0;
        // check input format error
        while(argv[3][j]!='\0'){
            if(!((argv[3][j]>=48 && argv[3][j]<=57) || (argv[3][j]=='.' )|| (argv[3][j] == '-'))){
                fprintf(stderr,"ERROR: Input format error at location %d.\n",j);
                return 1;
            }
            j++;
        }

         // check unwanted '.' in the input
        while(argv[3][k]!='\0'){
            if(argv[3][k]=='.'){
                ++count;
            }
            if(count>1){
                fprintf(stderr,"ERROR: Input format error at location %d.\n",k);
                return 1;
            }
            k++;
        }
        // Double --> Double
        if(argv[2][1]=='D'){
            fprintf(stdout,"%.6f\n",string2float(argv[3]));
        }
        // Double --> Float
        if(argv[2][1]=='F'){
            fprintf(stderr,"ERROR: This conversion is not possible.\n");
            return 1;
        }
        // Double --> Integer
        if(argv[2][1]=='I'){
            fprintf(stderr,"ERROR: This conversion is not possible.\n");
            return 1;
        }
        // Double --> Binary
        if(argv[2][1]=='B'){
            double2bin(string2float(argv[3]));
            for(j=0;j<64;j++){
                fprintf(stdout,"%d",bin64Arr[j]);
            }
            fprintf(stdout,"\n");
        }
         // Double --> Hexadecimal
        if(argv[2][1]=='H'){
            double2bin(string2float(argv[3]));
            double2hex();
        }
     }


    // Input format - Hexadecimal
      if(argv[1][1]=='H'){

        int count=0;

        while(argv[3][j]!='\0'){  // count the number of bits in the input
           count++;
            j++;
        }

        if(argv[2][1]!='D' && argv[2][1]!='B'){
            if(count<8){ // check the input size error
                fprintf(stderr,"ERROR: The input size is wrong.\n");
                return 1;
            }

            if(count>8){ // check the input size error
                fprintf(stderr,"ERROR: This conversion is not possible.\n");
                return 1;
            }
        }
        else{
            if(count<16){ // check the input size error
                fprintf(stderr,"ERROR: The input size is wrong.\n");
                return 1;
            }

            if(count>16){ // check the input size error
                fprintf(stderr,"ERROR: This conversion is not possible.\n");
                return 1;
            }
        }
        if(argv[2][1]=='B'){
            if(count<8){ // check the input size error
                fprintf(stderr,"ERROR: The input size is wrong.\n");
                return 1;
            }

            if(count>8 && count<16){ // check the input size error
                fprintf(stderr,"ERROR: This conversion is not possible.\n");
                return 1;
            }

            if(count>16){ // check the input size error
                fprintf(stderr,"ERROR: This conversion is not possible.\n");
                return 1;
            }
        }


        for(j=0;j<count;j++){    // check input format error
            if(!((argv[3][j] >= '0' && argv[3][j] <= '9') || (argv[3][j] >= 'A' && argv[3][j] <= 'F'))){
                fprintf(stderr,"ERROR: Input format error at location %d.\n",j);
                return 1;
            }
        }

        string2hex(argv[3]);

        // Hexadecimal --> Hexadecimal
        if(argv[2][1]=='H'){
            fprintf(stdout,"0x");
            for(j=0;j<8;j++){
                fprintf(stdout,"%c",hexArr[j]);
            }
            fprintf(stdout,"\n");
        }

         // Hexadecimal --> Binary
        if(argv[2][1]=='B'){
            if(count==8){
            hex2bin();
            for(j = 0 ; j< 32; j++){
                fprintf(stdout,"%d",binaryArr[j]);
            }
            fprintf(stdout,"\n");
            }
            else if(count==16){
            string2hex16(argv[3]);
            hex2bin64();
            for(j = 0 ; j< 64; j++){
                fprintf(stdout,"%d",bin64Arr[j]);
            }
            fprintf(stdout,"\n");
            }
        }

        // Hexadecimal --> Integer
        if(argv[2][1]=='I'){
            int value = hex2int();
            fprintf(stdout,"%d\n",value);
        }

        // Hexadecimal --> Float
        if(argv[2][1]=='F'){
            hex2float();
        }

        // Hexadecimal --> Double
        if( argv[2][1]=='D') {
            string2hex16(argv[3]);
            hex2double();
        }

     }

    return 0;
}

// convert string input to integer
long string2int(char *ch){

    int a,i=0,k,arr[32],j=1;
    long sum=0;
    if(ch[0]!='-'){
        while(ch[i]!='\0'){
            a = ch[i];
            arr[i]=a-48;
            ++i;
        }
        for(k=i-1;k>=0;k--){
            sum = sum + arr[k]*j;
            j=j*10;
        }
    }
    else{
        i=1;
        while(ch[i]!='\0'){
            a = ch[i];
            arr[i]=a-48;
            ++i;
        }
        for(k=i-1;k>=1;k--){
        sum= sum+arr[k]*j;
        j=j*10;
    }
    sum=sum*(-1);
    }

    return sum;

}

// convert string input to float
float string2float(char *ch){

   int a,i=0,k,arr[32],newArr[32],j=1,b;
    long int_val=0;
    float float_part=0;
    if(ch[0]!='-'){
        while(ch[i]!='.'){
            a = ch[i];
            arr[i]=a-48;
            ++i;
        }

        for(k=i-1;k>=0;k--){
            int_val = int_val + arr[k]*j;
            j=j*10;
        }

        k=0;
        i++;
        while(ch[i]!='\0'){
            a = ch[i];
            newArr[k]=a-48;
            ++i;
            k++;
        }

        float c=0.1;
        for(b=0;b<k;b++){
            float_part = float_part + newArr[b]*c;
            c=c/10;
        }
        return int_val+float_part;

    }
    else{
        i=1;
        while(ch[i]!='.'){
            a = ch[i];
            arr[i]=a-48;
            ++i;
        }
        for(k=i-1;k>=1;k--){
        int_val= int_val+arr[k]*j;
        j=j*10;
    }

        k=0;
        i++;
        while(ch[i]!='\0'){
            a = ch[i];
            newArr[k]=a-48;
            ++i;
            k++;
        }

        float c=0.1;
        for(b=0;b<k;b++){
            float_part = float_part + newArr[b]*c;
            c=c/10;
        }
        return (int_val+float_part)*(-1);

    }
}

// Integer --> Binary
void int2bin(int int_val){

    int i=0,j;
    for(j = 31 ; j>= 0; j--){
        binaryArr[j]=0;
    }

    if(int_val>0){    //when integer value > 0

        while(int_val!=0){
            binaryArr[i++]= int_val%2;
            int_val = int_val/2;
        }
    }
    else if(int_val<0){     // when integer value < 0

        int_val = int_val*(-1);

        while(int_val!=0){
            binaryArr[i++]= int_val%2;
            int_val = int_val/2;
        }

        for(i=31; i>=0; i--){
            if(binaryArr[i] == 0){
                binaryArr[i] = 1; continue;
            }
            if(binaryArr[i] == 1)
                binaryArr[i] = 0;

        }

        for(i=0; i<32; i++){
            if(binaryArr[i] == 0){
                binaryArr[i] = 1; break;
            }
            if(binaryArr[i] == 1)
                binaryArr[i] = 0;
        }

    }
}

// Integer --> Hexadecimal
void int2hex(){

    int newArr[32],i;

    for(i=0;i<32;i++){
        newArr[i] = binaryArr[31-i];
    }
    for(i=0;i<32;i++){
        binaryArr[i] = newArr[i];
    }

     bin2hex();

}

// convert string input to Binary
void string2bin(char * ch){

    int i=0,j;
    for(j = 31 ; j>= 0; j--){
        binaryArr[j]=0;
    }

     for(i=31; i>=0; i--){
        if((ch[i])==48 || (ch[i])==49){
            binaryArr[i] = ch[i]-48;
        }
    }

}

// convert 64bit String to Binary
void string2bin64(char *ch){

    int i=0,j;
    for(j = 63 ; j>= 0; j--){
        bin64Arr[j]=0;
    }

     for(i=63; i>=0; i--){
        if((ch[i])==48 || (ch[i])==49){
            bin64Arr[i] = ch[i]-48;
        }
    }
}

// Binary --> Integer
int bin2int(){

    int i,value=0,j=1;

    if(binaryArr[0]==1){

       for(i=31; i>=0; i--){
            if(binaryArr[i] == 0){
                binaryArr[i] = 1; continue;
            }
            if(binaryArr[i] == 1)
                binaryArr[i] = 0;

        }

        for(i=31; i>=0; i--){
            if(binaryArr[i] == 0){
                binaryArr[i] = 1; break;
            }
            if(binaryArr[i] == 1)
                binaryArr[i] = 0;
        }

        for(i=31; i>=0; i--){
        value = value + binaryArr[i]*j;
        j = j*2;
        }
        return value*(-1);
    }

    for(i=31; i>=0; i--){
        value = value + binaryArr[i]*j;
        j = j*2;
    }
    return value;
}

// Binary --> Hexadecimal
void bin2hex(){

    int i,j;

    for(i=28,j=0; i>=0 && j<8 ; i=i-4,j++){

        if( binaryArr[i]==0 && binaryArr[i+1]==0 && binaryArr[i+2]==0 && binaryArr[i+3]==0 )
            hexArr[j] = '0';
        else if( binaryArr[i]==0 && binaryArr[i+1]==0 && binaryArr[i+2]==0 && binaryArr[i+3]==1)
            hexArr[j] = '1';
        else if( binaryArr[i]==0 && binaryArr[i+1]==0 && binaryArr[i+2]==1 && binaryArr[i+3]==0 )
            hexArr[j] = '2';
        else if( binaryArr[i]==0 && binaryArr[i+1]==0 && binaryArr[i+2]==1 && binaryArr[i+3]==1 )
            hexArr[j] = '3';
        else if( binaryArr[i]==0 && binaryArr[i+1]==1 && binaryArr[i+2]==0 && binaryArr[i+3]==0 )
            hexArr[j] = '4';
        else if( binaryArr[i]==0 && binaryArr[i+1]==1 && binaryArr[i+2]==0 && binaryArr[i+3]==1 )
            hexArr[j] = '5';
        else if( binaryArr[i]==0 && binaryArr[i+1]==1 && binaryArr[i+2]==1 && binaryArr[i+3]==0 )
            hexArr[j] = '6';
        else if( binaryArr[i]==0 && binaryArr[i+1]==1 && binaryArr[i+2]==1 && binaryArr[i+3]==1  )
            hexArr[j] = '7';
        else if( binaryArr[i]==1 && binaryArr[i+1]==0 && binaryArr[i+2]==0 && binaryArr[i+3]==0 )
            hexArr[j] = '8';
        else if( binaryArr[i]==1 && binaryArr[i+1]==0 && binaryArr[i+2]==0 && binaryArr[i+3]==1 )
            hexArr[j] = '9';
        else if( binaryArr[i]==1 && binaryArr[i+1]==0 && binaryArr[i+2]==1 && binaryArr[i+3]==0 )
            hexArr[j] = 'A';
        else if( binaryArr[i]==1 && binaryArr[i+1]==0 && binaryArr[i+2]==1 && binaryArr[i+3]==1 )
            hexArr[j] = 'B';
        else if( binaryArr[i]==1 && binaryArr[i+1]==1 && binaryArr[i+2]==0 && binaryArr[i+3]==0 )
            hexArr[j] = 'C';
        else if( binaryArr[i]==1 && binaryArr[i+1]==1 && binaryArr[i+2]==0 && binaryArr[i+3]==1  )
            hexArr[j] = 'D';
        else if( binaryArr[i]==1 && binaryArr[i+1]==1 && binaryArr[i+2]==1 && binaryArr[i+3]==0 )
            hexArr[j] = 'E';
        else if( binaryArr[i]==1 && binaryArr[i+1]==1 && binaryArr[i+2]==1 && binaryArr[i+3]==1 )
            hexArr[j] = 'F';
    }
}

// Binary --> Float
void bin2float(){

    int i,arr[8],sum=0,j=1,int_val=0;
    float float_val=0,k=0.5;

    // get the exponent
    for(i=1;i<=8;i++){
        arr[i-1] = binaryArr[i];
    }

    for(i=7;i>=0;i--){
        sum = sum + j*arr[i];
        j = j*2;
    }

    int exponent = sum - 127;

    if(exponent>0){
        j=1;
         // get the int value
        for(i=8+exponent;i>=9;i--){
            int_val = int_val + j*binaryArr[i];
            j=j*2;
        }
        int_val = int_val + j;

        // get the floating point numbers
        for(i=9+exponent;i<32;i++){
            float_val = float_val + k*binaryArr[i];
            k=k/2;
        }

         // print the output
        if(binaryArr[0]==0)
            fprintf(stdout,"%.2f\n",int_val+float_val);
        if(int_val!=0 && binaryArr[0]==1)
            fprintf(stdout,"%.2f\n",(int_val+float_val)*(-1));
    }

    if(exponent<0){
        exponent = exponent*(-1);

         // get the floating point numbers
         int Arr[exponent];
         for(i=0;i<=exponent-2;i++){
            Arr[i]=0;
         }
         Arr[exponent-1] = 1;

         k=0.5;
         for(i=0;i<=exponent-1;i++){
            float_val = float_val + k*Arr[i];
            k=k/2;
        }
        for(i=9;i<32;i++){
            float_val = float_val + k*binaryArr[i];
            k=k/2;
        }

         // print the output
        if(binaryArr[0]==0)
            fprintf(stdout,"%.2f\n",float_val);
        if(float_val!=0 && binaryArr[0]==1)
            fprintf(stdout,"%.2f\n",(float_val)*(-1));
    }

}

// Binary --> Double
void bin2double(){

    int i,arr[11],sum=0,j=1,int_val=0;
    float float_val=0,k=0.5;

    // get the exponent
    for(i=1;i<=11;i++){
        arr[i-1] = bin64Arr[i];
    }

    for(i=10;i>=0;i--){
        sum = sum + j*arr[i];
        j = j*2;
    }
    int exponent = sum - 1023;

    // get the int value
    if(exponent>0){
        j=1;
        for(i=11+exponent;i>=12;i--){
            int_val = int_val + j*bin64Arr[i];
            j=j*2;
        }
        int_val = int_val + j;

        // get the floating point numbers
        for(i=12+exponent;i<64;i++){
            float_val = float_val + k*bin64Arr[i];
            k=k/2;
        }
        // print the output
        if(bin64Arr[0]==0)
            fprintf(stdout,"%.6f\n",int_val+float_val);
        if(int_val!=0 && bin64Arr[0]==1)
            fprintf(stdout,"%.6f\n",(int_val+float_val)*(-1));
        }



    if(exponent<0){
        exponent = exponent*(-1);
         // get the floating point numbers
         int arr[exponent];
         k=0.5;
         for(i=0;i<=exponent-2;i++){
            arr[i]=0;
         }
         arr[exponent-1] = 1;


         for(i=0;i<=exponent-1;i++){
            float_val = float_val + k*arr[i];
            k=k/2;
        }

        for(i=12;i<64;i++){
            float_val = float_val + k*bin64Arr[i];
            k=k/2;
        }

         // print the output
        if(bin64Arr[0]==0)
            fprintf(stdout,"%f\n",float_val);
        if(float_val!=0 && bin64Arr[0]==1)
            fprintf(stdout,"%f\n",(float_val)*(-1));
    }
}

// convert string input to Hexadecimal char array
void string2hex(char *ch){

    int i=0;

     for(i=7; i>=0; i--){
        hexArr[i] = ch[i];
    }
}

// Hexadecimal --> Integer
int hex2int(){
    hex2bin();
    int value = bin2int();
    return value;

}

// Hexadecimal --> Binary
void hex2bin(){

    int i,j;
    for(i=0,j=0; i<8 && j<=28; i++,j=j+4)
    {
        switch(hexArr[i])
        {
        case '0':
            binaryArr[j] = 0; binaryArr[j+1] = 0; binaryArr[j+2] = 0; binaryArr[j+3] = 0;
            break;
        case '1':
            binaryArr[j] = 0; binaryArr[j+1] = 0; binaryArr[j+2] = 0; binaryArr[j+3] = 1;
            break;
        case '2':
            binaryArr[j] = 0; binaryArr[j+1] = 0; binaryArr[j+2] = 1; binaryArr[j+3] = 0;
            break;
        case '3':
            binaryArr[j] = 0; binaryArr[j+1] = 0; binaryArr[j+2] = 1; binaryArr[j+3] = 1;
            break;
        case '4':
            binaryArr[j] = 0; binaryArr[j+1] = 1; binaryArr[j+2] = 0; binaryArr[j+3] = 0;
            break;
        case '5':
            binaryArr[j] = 0; binaryArr[j+1] = 1; binaryArr[j+2] = 0; binaryArr[j+3] = 1;
            break;
        case '6':
            binaryArr[j] = 0; binaryArr[j+1] = 1; binaryArr[j+2] = 1; binaryArr[j+3] = 0;
            break;
        case '7':
            binaryArr[j] = 0; binaryArr[j+1] = 1; binaryArr[j+2] = 1; binaryArr[j+3] = 1;
            break;
        case '8':
            binaryArr[j] = 1; binaryArr[j+1] = 0; binaryArr[j+2] = 0; binaryArr[j+3] = 0;
            break;
        case '9':
            binaryArr[j] = 1; binaryArr[j+1] = 0; binaryArr[j+2] = 0; binaryArr[j+3] = 1;
            break;
        case 'A':
            binaryArr[j] = 1; binaryArr[j+1] = 0; binaryArr[j+2] = 1; binaryArr[j+3] = 0;
            break;
        case 'B':
            binaryArr[j] = 1; binaryArr[j+1] = 0; binaryArr[j+2] = 1; binaryArr[j+3] = 1;
            break;
        case 'C':
            binaryArr[j] = 1; binaryArr[j+1] = 1; binaryArr[j+2] = 0; binaryArr[j+3] = 0;
            break;
        case 'D':
            binaryArr[j] = 1; binaryArr[j+1] = 1; binaryArr[j+2] = 0; binaryArr[j+3] = 1;
            break;
        case 'E':
            binaryArr[j] = 1; binaryArr[j+1] = 1; binaryArr[j+2] = 1; binaryArr[j+3] = 0;
            break;
        case 'F':
            binaryArr[j] = 1; binaryArr[j+1] = 1; binaryArr[j+2] = 1; binaryArr[j+3] = 1;
            break;
        }
    }

}

// Hexadecimal --> Float
void hex2float(){
    hex2bin();
    bin2float();

}

// Hexadecimal --> Double
void hex2double(){
    hex2bin64();
    bin2double();
}

// convert 16 bit string hexadecimal input to char array
void string2hex16(char *ch){

    int i=0;

     for(i=15; i>=0; i--){
        hexArr16[i] = ch[i];
    }

}

//  Hexadecimal(16 bit) -->  Binary(64 bit)
void hex2bin64(){

    int i,j;
    for(i=0,j=0; i<16 && j<=60; i++,j=j+4)
    {
        switch(hexArr16[i])
        {
        case '0':
            bin64Arr[j] = 0; bin64Arr[j+1] = 0; bin64Arr[j+2] = 0; bin64Arr[j+3] = 0;
            break;
        case '1':
            bin64Arr[j] = 0; bin64Arr[j+1] = 0; bin64Arr[j+2] = 0; bin64Arr[j+3] = 1;
            break;
        case '2':
            bin64Arr[j] = 0; bin64Arr[j+1] = 0; bin64Arr[j+2] = 1; bin64Arr[j+3] = 0;
            break;
        case '3':
            bin64Arr[j] = 0; bin64Arr[j+1] = 0; bin64Arr[j+2] = 1; bin64Arr[j+3] = 1;
            break;
        case '4':
            bin64Arr[j] = 0; bin64Arr[j+1] = 1; bin64Arr[j+2] = 0; bin64Arr[j+3] = 0;
            break;
        case '5':
            bin64Arr[j] = 0; bin64Arr[j+1] = 1; bin64Arr[j+2] = 0; bin64Arr[j+3] = 1;
            break;
        case '6':
            bin64Arr[j] = 0; bin64Arr[j+1] = 1; bin64Arr[j+2] = 1; bin64Arr[j+3] = 0;
            break;
        case '7':
            bin64Arr[j] = 0; bin64Arr[j+1] = 1; bin64Arr[j+2] = 1; bin64Arr[j+3] = 1;
            break;
        case '8':
            bin64Arr[j] = 1; bin64Arr[j+1] = 0; bin64Arr[j+2] = 0; bin64Arr[j+3] = 0;
            break;
        case '9':
            bin64Arr[j] = 1; bin64Arr[j+1] = 0; bin64Arr[j+2] = 0; bin64Arr[j+3] = 1;
            break;
        case 'A':
            bin64Arr[j] = 1; bin64Arr[j+1] = 0; bin64Arr[j+2] = 1; bin64Arr[j+3] = 0;
            break;
        case 'B':
            bin64Arr[j] = 1; bin64Arr[j+1] = 0; bin64Arr[j+2] = 1; bin64Arr[j+3] = 1;
            break;
        case 'C':
            bin64Arr[j] = 1; bin64Arr[j+1] = 1; bin64Arr[j+2] = 0; bin64Arr[j+3] = 0;
            break;
        case 'D':
            bin64Arr[j] = 1; bin64Arr[j+1] = 1; bin64Arr[j+2] = 0; bin64Arr[j+3] = 1;
            break;
        case 'E':
            bin64Arr[j] = 1; bin64Arr[j+1] = 1; bin64Arr[j+2] = 1; bin64Arr[j+3] = 0;
            break;
        case 'F':
            bin64Arr[j] = 1; bin64Arr[j+1] = 1; bin64Arr[j+2] = 1; bin64Arr[j+3] = 1;
            break;
        }
    }
}

// Float --> Binary
void float2bin(float f){

    int count=0,i,j,k,arr[32],newValue,expArr[8];
    float floatPart,newf;

    if(f<0)
        newf=f*(-1);
    else
        newf=f;

    int intPart = newf;
    int2bin(intPart);

    for(i=0;i<32;i++){
        arr[i]=0;
    }

    for(i=31;i>=0;i--){
        if(binaryArr[i]==0)
            count++;
        if(binaryArr[i]==1)
            break;
    }

    for(j=0;j<(32-count);j++){
        arr[j] = binaryArr[i];
        i--;
    }
    i=j-1;
   floatPart = newf-intPart;

   k=0;
   while(floatPart!=0.0){
        if(k==0)
        floatPart = floatPart*2;
        newValue = floatPart;
        arr[j]=newValue;
        floatPart = (floatPart-newValue)*2;
        j++;
        k++;
   }

    int exponent = 127+i;
    for(j=0;j<8;j++){
        expArr[j]=0;
    }

    k=0;
    while(exponent != 0){
        expArr[7-k] = exponent%2;
        exponent = exponent/2;
        k++;
    }



    for(j=1;j<9;j++){
        binaryArr[j] = expArr[j-1];
    }

    k=1;
    for(j=9;j<32;j++){
        binaryArr[j]= arr[k];
        k++;
    }
    if(f<0)
        binaryArr[0]=1;
    else
        binaryArr[0]=0;
}

// Float --> Hexadecimal
void float2hex(){
    int i;
    bin2hex();
    fprintf(stdout,"0x");
    for(i=7;i>=0;i--){
        fprintf(stdout,"%c",hexArr[i]);
    }
    fprintf(stdout,"\n");
}

//Double --> Binary
void double2bin(float f){

    int count=0,i,j,k,arr[64],newValue,expArr[11];
    float floatPart,newf;

    if(f<0)
        newf=f*(-1);
    else
        newf=f;

    int intPart = newf;
    int2bin(intPart);

    for(i=0;i<64;i++){
        arr[i]=0;
    }

    for(i=31;i>=0;i--){
        if(binaryArr[i]==0)
            count++;
        if(binaryArr[i]==1)
            break;
    }
    for(j=0;j<(32-count);j++){
        arr[j] = binaryArr[i];
        i--;
    }
    i=j-1;
   floatPart = newf-intPart;

    k=0;
   while(floatPart!=0.0){
       if(k==0)
         floatPart = floatPart*2;
       newValue = floatPart;
       arr[j] = newValue;
       floatPart = (floatPart-newValue)*2;
       j++;
        k++;
   }

    int exponent = 1023+i;
    for(j=0;j<12;j++){
        expArr[j]=0;
    }

    k=0;
    while(exponent != 0){
        expArr[10-k] = exponent%2;
        exponent = exponent/2;
        k++;
    }

    for(j=1;j<11;j++){
        bin64Arr[j] = expArr[j-1];
    }

    k=1;
    for(j=12;j<64;j++){
        bin64Arr[j]= arr[k];
        k++;
    }
    if(f<0)
        bin64Arr[0]=1;
    else
        bin64Arr[0]=0;

}

// Double --> Hexadecimal
void double2hex(){
    int i;
    bin2hex16();
    fprintf(stdout,"0x");
    for(i=15;i>=0;i--){
        fprintf(stdout,"%c",hexArr16[i]);
    }
    fprintf(stdout,"\n");
}


// Binary (64 bits)--> Hexadecimal(16 bits)
void bin2hex16(){

    int i,j;

    for(i=60,j=0; i>=0 && j<16 ; i=i-4,j++){

        if( bin64Arr[i]==0 && bin64Arr[i+1]==0 && bin64Arr[i+2]==0 && bin64Arr[i+3]==0 )
            hexArr16[j] = '0';
        else if( bin64Arr[i]==0 && bin64Arr[i+1]==0 && bin64Arr[i+2]==0 && bin64Arr[i+3]==1)
            hexArr16[j] = '1';
        else if( bin64Arr[i]==0 && bin64Arr[i+1]==0 && bin64Arr[i+2]==1 && bin64Arr[i+3]==0 )
            hexArr16[j] = '2';
        else if( bin64Arr[i]==0 && bin64Arr[i+1]==0 && bin64Arr[i+2]==1 && bin64Arr[i+3]==1 )
            hexArr16[j] = '3';
        else if( bin64Arr[i]==0 && bin64Arr[i+1]==1 && bin64Arr[i+2]==0 && bin64Arr[i+3]==0 )
            hexArr16[j] = '4';
        else if( bin64Arr[i]==0 && bin64Arr[i+1]==1 && bin64Arr[i+2]==0 && bin64Arr[i+3]==1 )
            hexArr16[j] = '5';
        else if( bin64Arr[i]==0 && bin64Arr[i+1]==1 && bin64Arr[i+2]==1 && bin64Arr[i+3]==0 )
            hexArr16[j] = '6';
        else if( bin64Arr[i]==0 && bin64Arr[i+1]==1 && bin64Arr[i+2]==1 && bin64Arr[i+3]==1 )
            hexArr16[j] = '7';
        else if( bin64Arr[i]==1 && bin64Arr[i+1]==0 && bin64Arr[i+2]==0 && bin64Arr[i+3]==0 )
            hexArr16[j] = '8';
        else if( bin64Arr[i]==1 && bin64Arr[i+1]==0 && bin64Arr[i+2]==0 && bin64Arr[i+3]==1 )
            hexArr16[j] = '9';
        else if( bin64Arr[i]==1 && bin64Arr[i+1]==0 && bin64Arr[i+2]==1 && bin64Arr[i+3]==0 )
            hexArr16[j] = 'A';
        else if( bin64Arr[i]==1 && bin64Arr[i+1]==0 && bin64Arr[i+2]==1 && bin64Arr[i+3]==1 )
            hexArr16[j] = 'B';
        else if( bin64Arr[i]==1 && bin64Arr[i+1]==1 && bin64Arr[i+2]==0 && bin64Arr[i+3]==0 )
            hexArr16[j] = 'C';
        else if( bin64Arr[i]==1 && bin64Arr[i+1]==1 && bin64Arr[i+2]==0 && bin64Arr[i+3]==1 )
            hexArr16[j] = 'D';
        else if( bin64Arr[i]==1 && bin64Arr[i+1]==1 && bin64Arr[i+2]==1 && bin64Arr[i+3]==0 )
            hexArr16[j] = 'E';
        else if( bin64Arr[i]==1 && bin64Arr[i+1]==1 && bin64Arr[i+2]==1 && bin64Arr[i+3]==1 )
            hexArr16[j] = 'F';
    }
}

