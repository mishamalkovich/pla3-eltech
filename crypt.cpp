#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>

using namespace std;
    int main(int argc, char* argv[]){
         int chc=0, key=0, keycounter=0, error=0;   // for 'chc' 0 - encode, 1 - decode          
         string option, newalphabet="0", addopt;        
         for (int i=1; i<argc; i++)
            option.assign(argv[i]);
            addopt.assign(argv[i+1]);
            if ((option == "-t") && (addopt == "decode")){
                chc = 1;error=error+2;
            }
            if ((option == "-t") && (addopt == "encode")){
                error=error+2;
            }
            if (option == "-t=decode"){
                error++;
                chc =1;
            }
            if (option == "-t=encode"){
                error++;
            }
            if ((option == "-h") || (option == "--help")){
                system ("Help.txt"); 
                error++;
            }
            if ((option == "-a") && (addopt !="-t")){
                newalphabet = argv[i+1];
                error++;
                i++;
            }
            if ((atoi(argv[i])>-10) && (atoi(argv[i])< 10)) { 
                k = atoi(argv[i]);
                 error++;
                 keycounter=i;
                 break;
            }
            if (error==0){
                cout<<"Bad options. Call help\n";
                return 1;
            }
            error--;

            if ((keycounter == 0) && (error != 0)) {
                cout<<"Oops. Parametres are incorrect"; 
                system ("Help.txt");
            }
            if (key <= 0){
                cout<<"Bad key. Call help\n";
                return 2;
            }


            const char *inputfile;
            const char *outputfile;
            if ((keycounter+3) == argc) {
                inputfile=argv[keycounter+1];
                outputfile= argv[keycounter+2];
            }
            if ((keycounter+2) == argc) {
                inputfile=argv[keycounter+1];
                outputfile= argv[keycounter+1];
            }
            //if decoding — we use negative key
            if(chc==1){
                key*=(-1);
            }
            FILE *inset,*outset;
            inset = fopen(inputfile, "r+");
            if (inset == NULL) {
                cout<<"Unknown file\n";
                 return 3;
            }

             vector <char> codresult;
             bool alphabet = (newalphabet != "0"); 
             char param;  
             while (!feof(inset)){ 
             fread (&param ,sizeof(char) , 1, inset);
             int symbol=int(param);
             if (feof(inset)) break;
             if (alphabet && newalphabet.find(param,0)==-1) {
                codresult.push_back(param);
                 continue;
             }            
             //zaglavnye latin bukvy

             if((symbol >= 65) && (symbol <= 90)){
             symbol = (char)(65 + ((symbol -65 + k + 26*chc) %26));
         }
         //strochnye latin bukvy

         if((symbol >= 97) && (symbol <= 122)){
            symbol = (char)(97 + ((symbol - 97 + k + 26*chc) % 26));
        }
        //numbers

        if((symbol >= 48) && (symbol <= 57)){
            symbol = (char)( 48+ ((symbol - 48 + k + 10*type) %10));
        }
        if ((symbol < 48) || ((symbol > 57) && (symbol < 65)) || ((symbol > 90) && (symbol < 97)) || (symbol > 122)){
            symbol = (char)(symbol);
        }
            codresult.push_back(symbol);    //others symbols don't change
        }

        fclose(inset);
        int size = (int) result.size();
        outset = fopen(outputfile, "wb");
        for (int i =0; i < size; i++) fwrite(&result[i],sizeof(char),1,outset);
            cout<<"All right!\n";

        getch();
        return 0;
    }
