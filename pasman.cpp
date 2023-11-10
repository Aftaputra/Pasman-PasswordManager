#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <Windows.h>

//data = jemput txt
//myfile = simpan txt
using namespace std;


string Encrypt(string password, string key){
    // used to convert string to integer of the key
    // used as temporary variable for the converted password
    unsigned char pass;
    for(int i = 0; i < password.length(); i++){
        pass = (unsigned char)((unsigned char)password[i] ^ (unsigned char)key[i % (key.length())]);
        password[i] = (unsigned char)(pass) + 128;
    }

    return password;
}

string Decypt(string password, string key){
    // used to convert string to integer of the key
    // used as temporary variable for the converted password
    unsigned char pass;
    for(int i = 0; i < password.length(); i++){
        pass = (unsigned char)((unsigned char)(password[i] - 128) ^ (unsigned char)key[i % (key.length())]);
        password[i] = (unsigned char)(pass);
    }

    return password;
}

void DisplayAll(string key) {
    string content[10000][2];
    ifstream data("data.txt"); //deklarasi file
    //jika file pass.txt bisa terbuka,
    if(data.is_open()){
        //masukkan isi pass.txt ke array content[][]
        // nanti forloops diganti while sampai EOF
        int i = 0;
        while(true){
            if(data.eof()){
                break;
            }
            else {
                cout << i + 1 << ".";
                for(int j = 0; j < 2; j++){
                    data >> content[i][j];
                     
                    cout << Decypt(content[i][j], key) << " ";
                    // cout << content[i][j] << " ";
                }
                cout << endl;
                i++;
            }
        } 
    }

    data.close();
}

void Saving(string saved[]) {
    ofstream myfile("data.txt", fstream::app);
    if(myfile.is_open()){     
        for(int j = 0; j < 2; j++){ //inner untuk 2 input akun & pass
            myfile << saved[j] << " ";
        }
        myfile << endl;
        
    }
    else {
        cout << "File tidak dapat dibuka/ditemukan";
    }

    myfile.close();
}

string Generate(int panjang){
    const string cha = "1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:ZXCVBNM<>?";
    string pw;
    for (int i=0;i<panjang;i++){
        int chpw= rand() % cha.size();
        pw += cha[chpw];
        
    }

    return pw;
}


int main() {
    
        cout << R"(
 #####    ##       #####     ####     #####  
 ##       ##       ##  ##   ##  ##   ##      
 ####     ##       #####    ######    ####   
 ##       ##       ##       ##  ##       ##  
 #####    #####    ##       ##  ##   #####                                              
    )"; 
    cout << endl;
    cout << "======= Elins Password Manager v.0.1 ======";
    cout << endl;
    cout << endl;
    while(true){
        cout << "Silakan pilih fitur yang diinginkan : " << endl;
        cout << "1. Input Manual Password" << endl << "2. Auto-generated Password" << endl << "3. Look-up saved password" << endl << "4. Exit" ;
        cout << endl;
        
        int x;
        cout << "Masukkan angka (1 - 4) = ";
        cin >> x;

        if(x == 1){
            // //input manual
            string key;
            string InputAcc[2];
            cout << "Masukkan Key = ";
            cin >> key;
            cout << "Masukkan ID & Password = ";
            for(int i = 0; i < 2; i++){
                cin >> InputAcc[i];
                InputAcc[i] = Encrypt(InputAcc[i], key);
            }
            Saving(InputAcc);
            cout << "Data berhasil disimpan!" << endl;
            cout << endl;
            Sleep(1000);
        }
        else if(x == 2){
            //generate random
            string key;
            int ln;
            string InputAcc[2];
            cout << "Masukkan Key = ";
            cin >> key;
            cout << "Masukkan ID = ";
            cin >> InputAcc[0];
            cout << "Masukkan Panjang Password= ";
            cin >> ln;
            InputAcc[1] = Generate(ln);
            cout << "Password: " << InputAcc[1] << endl; 
            for(int i = 0; i < 2; i++){
                InputAcc[i] = Encrypt(InputAcc[i], key);
            }
            Saving(InputAcc);
            cout << "Password: " << InputAcc[1] << endl; 
            cout << "Data berhasil disimpan!" << endl;
            cout << endl;

        }
        else if(x == 3){
            //lookup
            string key;
            cout << "Masukkan key = ";
            cin >> key;
            DisplayAll(key);
            cout << endl;
        } 
        else if(x == 4){
            //exit
            cout << "Terimakasih!";
            cout << endl;
            break;
        } 
        else {
            cout << "Masukkan angka sesuai opsi(1-4) yang Benar";
            cout << endl;
            continue;
        }
    }
}
