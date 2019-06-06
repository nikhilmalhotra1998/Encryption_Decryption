#include <iostream>
#include <cstring>
#include <unordered_map>
#include<fstream>
using namespace std;
#define N 2 

  
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n) 
{ 
    int i = 0, j = 0; 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
  
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
    
} 
  

int determinant(int A[N][N], int n) 
{ 
    int D = 0; 
    if (n == 1) 
        return A[0][0]; 
  
    int temp[N][N];
  
    int sign = 1;  
  

    for (int f = 0; f < n; f++) 
    { 
    
        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n - 1); 
  
     
        sign = -sign; 
    } 
    
    if(D<0){
		D=26+D;
	}
  for(int i=1;i<D;i++){
  	if((D*i)%26==1){
  		return i;
	  }
  }
    return D; 
} 
  
 
void adjoint(int A[N][N],int adj[N][N]) 
{ 
    if (N == 1) 
    { 
        adj[0][0] = 1; 
        return; 
    } 
   
    int sign = 1, temp[N][N]; 
  
    for (int i=0; i<N; i++) 
    { 
        for (int j=0; j<N; j++) 
        {
            getCofactor(A, temp, i, j, N); 
  
           
            sign = ((i+j)%2==0)? 1: -1; 
  
            adj[j][i] = (sign)*(determinant(temp, N-1)); 
        } 
    } 
    for (int i = 0; i < N;i++) 
    { 
        for (int j = 0; j < N; j++) 
        { 
        if(adj[i][j]<0){
        	adj[i][j]=26+adj[i][j];
		}
	}
	
}
} 

void inverse(int A[N][N],int inverse[N][N]) 
{ 
 
    int det = determinant(A, N); 
    if (det == 0) 
    { 
        cout << "Singular matrix, can't find its inverse"; 
        return;
    } 
  

    int adj[N][N]; 
    adjoint(A, adj); 
  
  
    for (int i=0; i<N; i++) 
        for (int j=0; j<N; j++) 
            inverse[i][j] = (adj[i][j]*det)%26; 
   
}
 
class StraddlingCheckerboard
{
  unordered_map<char, string> table;
  char first[10], second[10], third[10];
  int rowU, rowV;
 
public:
  StraddlingCheckerboard(const string &alphabet, int u, int v)
  {
    rowU = min(u, v);
    rowV = max(u, v);
 
    for(int i = 0, j = 0; i < 10; ++i)
    {
      if(i != u && i != v)
      {
        first[i] = alphabet[j];
        table[alphabet[j]] = '0' + i;
        ++j;
      }
 
      second[i] = alphabet[i+8];
      table[alphabet[i+8]] = '0' + rowU;
      table[alphabet[i+8]] += '0' + i;
 
      third[i] = alphabet[i+18];
      table[alphabet[i+18]] = '0' + rowV;
      table[alphabet[i+18]] += '0' + i;
    }
  }
 
  string encode(const string &plain)
  {
    string out;
    for(int i = 0; i < plain.size(); ++i)
    {
      char c = plain[i];
      if(c >= 'a' && c <= 'z')
        c += 'A' - 'a';
 
      if(c >= 'A' && c <= 'Z')
        out += table[c];
      else if(c >= '0' && c <= '9')
      {
        out += table[' '];
        out += c;
      }
    }
    return out;
  }
 
  string decode(const string &cipher)
  {
    string out;
    int state = 0;
    for(int i = 0; i < cipher.size(); ++i)
    {
      int n = cipher[i] - '0';
      char next = 0;
 
      if(state == 1)
        next = second[n];
      else if(state == 2)
        next = third[n];
      else if(state == 3)
        next = cipher[i];
      else if(n == rowU)
        state = 1;
      else if(n == rowV)
        state = 2;
      else
        next = first[n];
 
      if(next == '/')
        state = 3;
      else if(next != 0)
      {
        state = 0;
        out += next;
      }
    }
    return out;
  }
};

int main()
{
  StraddlingCheckerboard encrypt("QWERTYUIOPASDFGHJKLZXCVBNM./", 3, 7);
 ifstream file;
 string line;
 char extra;
 int flag=0;
 cout<<"___________Welcome___________"<<endl;

 label: cout<<"Select Option to continue"<<endl;
 cout<<endl<<"1. Encrypt code"<<endl<<"2. Decrypt code"<<endl<<"3. Exit"<<endl;
 int x;
 cin>>x;
 switch(x){
 
 case 1:
 	{
	 cout<<"enter 4 letter key to encrypt data from- hill, pill, roll"<<endl;
	 	char hill_char[2][2];
	 	int hill[2][2];
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			cin>>hill_char[i][j];
			hill[i][j]=hill_char[i][j]-97;
			//cout<<msg1[i][j]<<" ";
		}
		//cout<<endl;
	}
 	string q;
 	cout<<endl<<"enter file name whose data you wish to encrypt"<<endl;
 	cin>>q;
 
 
 
 
	 file.open(q);
	 if (file.is_open())
 	 {
    while ( getline (file,line))
    
    
	 file.close();
	}
	cout << "message: " << line << endl;
	int c=0;
	int n=line.size()/2;
	ofstream myfile1;
  		myfile1.open ("extra.txt");
	if(line.size()%2==1){
		extra=line[line.size()-1];
		flag=1;
		
  		myfile1 << extra;
  		
	}
	else{
		myfile1<<" ";
	}
	myfile1.close();
	char msg[2][n];
	int msg1[2][n];
	for(int i=0;i<n;i++){
	for(int j=0;j<2;j++){
	msg[j][i]=line[c++];
		
	}
	}
	int en[2][n];
	char encrypt1[2][n];
	for(int i=0;i<2;i++){
		for(int j=0;j<n;j++){
			msg1[i][j]=msg[i][j]-97;
			//cout<<msg1[i][j]<<" ";
		}
		//cout<<endl;
	}
	cout<< "----------------encrypted-----------"<<endl;
	 for(int i=0;i<2;++i)
        {
            for(int j=0;j<n;++j)
            {
                en[i][j]=0;
                for(int k=0;k<2;++k)
                    en[i][j]=en[i][j]+(hill[i][k]*msg1[k][j]);
                    en[i][j]=(en[i][j]%26);
                    encrypt1[i][j]=en[i][j]+97;
                
				
        }
            
        }
        string line2=line;
        int y=0;
        		for(int i=0;i<n;i++){
		for(int j=0;j<2;j++){
			//cout<<encrypt1[j][i];
			line2[y++]=encrypt1[j][i];
			}
		}
	cout<<endl;
///////////////////////////////////

  	string original = line2;
  	string enC = encrypt.encode(original);
  
  		
  cout<<"after HILL Cipher: "<<original<<endl;
cout<<"after Straddling checkerboard: "<<endl;  
 
  
  		cout << "Encoded:  " << enC << endl;
 		cout<<endl<<"Write name of file in which you want to save encrypted text"<<endl;
 		string filename;
 		cin>>filename;
		 ofstream myfile;
  		myfile.open (filename);
  		myfile << enC;
  		myfile.close();
   cout<<endl<<"Encrypted text is saved in "<<filename<<" file.";
   cout<<endl<<endl;
  cout<<"**********************************************************************"<<endl<<endl;
  cout<<"Do you want to continue...(y/n)?"<<endl;
  char s;
  cin>>s;
  if(s=='y'||s=='Y'){
  	goto label;
  }
  else{
  	return 0;
  }
  		
		break;
  }
	case 2:
{
	cout<<"enter 4 letter key to decrypt data from- hill, pill, roll"<<endl;
	
	
	 	char dypt_char[2][2];
	 	int dypt[2][2];
		 int dypt_n[2][2];
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			cin>>dypt_char[i][j];
			dypt_n[i][j]=dypt_char[i][j]-97;
			//cout<<msg1[i][j]<<" ";
		}
		//cout<<endl;
	}
	inverse(dypt_n, dypt) ;
	
		string a;
 	cout<<endl<<"enter file name whose data you wish to decode"<<endl;
 	cin>>a;
	string newline;
	file.open(a);
 if (file.is_open())
  {
    while ( getline (file,newline))
    
    
 file.close();
}
	string de = encrypt.decode(newline);
  //cout << "Decoded:  " << de << endl;
  int n=de.length()/2;
  /////////////////////////////////

	char msg2[2][n];
	int z=0;
int msg3[2][n];
	for(int i=0;i<n;i++){
	for(int j=0;j<2;j++){
	msg2[j][i]=de[z++];
		
	}
}
	for(int i=0;i<2;i++){
		for(int j=0;j<n;j++){
			msg3[i][j]=msg2[i][j]-65;
			//cout<<msg1[i][j]<<" ";
		}
		//cout<<endl;
	}
	

  
  
  
  
  
  
  
  	////// dycryption
  	
  	
	char ans[2][n];
	int ans1[2][n];
	for(int i=0;i<2;++i)
        {
            for(int j=0;j<n;++j)
            {
                ans1[i][j]=0;
                for(int k=0;k<2;++k)
                    ans1[i][j]=ans1[i][j]+(dypt[i][k]*msg3[k][j]);
                    ans[i][j]=(ans1[i][j]%26)+97;
                
        }
        
        }
	

	cout<<endl<< "----------------dycrypted-----------"<<endl;
	cout<<"DECODE: ";
		for(int i=0;i<n;i++){
		for(int j=0;j<2;j++){
			cout<<ans[j][i];
	}
	}
	string newline1;
	file.open("extra.txt");
 if (file.is_open())
  {
    while ( getline (file,newline1))
    
    
 file.close();
}
		cout<<newline1;
	
  
  cout<<endl<<"Your code is decrypted."<<endl<<endl;
  cout<<"**********************************************************************"<<endl<<endl;
  cout<<"Do you want to continue...(y/n)?"<<endl;
  char s;
  cin>>s;
  if(s=='y'||s=='Y'){
  	goto label;
  }
  else{
  	return 0;
  }
 break;
}
 case 3:
  return 0;

}
}
