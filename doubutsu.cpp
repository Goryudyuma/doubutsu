#include <bits/stdc++.h>

using namespace std;

typedef long long unsigned int ll;

/*ll
 * 各マス
 * {
 * 味方:+5 敵:+0
 * ライオン:5
 * キリン:4
 * ぞう:3
 * 鶏:2
 * ひよこ:1
 *
 * 空きマス:0
 * }*12
 *
 * 持ち駒
 * {
 * キリン:0~2
 * ぞう:0~2
 * ひよこ:0~2
 * }*2
 * 味方-敵の順
 *
 * 
 * 12*4+3*2*2=60
 *
 * 初期状態
 * 0100 0101 0011
 * 0000 0001 0000
 * 0000 0110 0000
 * 1000 1010 1001
 *
 * 00 00 00
 * 00 00 00
 * */

template <typename T>
inline std::string to_bin_str(T n) {
	std::string str;
	while (n > 0) {
		str.push_back('0' + (n & 1));
		n >>= 1;
	}
	std::reverse(str.begin(), str.end());
	return str;
}



ll reverse(ll in){
	ll out=0,memo=0;
	out+=(in%(1L<<12))/(1L<<6);
	out+=(in%(1L<<6))*(1L<<6);
	memo=out;
	in>>=12;
	for (int i = 0; i < 12; i++) {
		int x=in%(1L<<4);
		in/=(1L<<4);
		ll y;
		if(x==0)y=0;
		else if(x>5){
			y=x-5;
		}else{
			y=x+5;
		}
		ll j=11L-i;
		out+=y<<(12L+j*4L);
		memo+=y<<(12L+(j/3L*3L+(2L-j%3L))*4L);
	}
	//cout<<"!"<<to_bin_str(out)<<endl<<"?"<<to_bin_str(memo)<<endl<<endl;
	return min(out,memo);
}

int main ()
{
	vector<ll>data;
	set<ll>data_set;
	ll i;
	ll first_=reverse(0B010001010011000000010000000001100000100010101001000000000000);
	data.push_back(first_);
	data_set.insert(first_);
	cout<<to_bin_str(data[0])<<endl;
	cout<<to_bin_str(reverse(data[0]))<<endl;
	for (i = 0; i < data.size(); i++) {
		ll now=data[i];
		vector<vector<ll>> now_board(5,vector<ll>(3));
		now_board[4][0]=now/(1L<<8L)%(1L<<6L);
		now_board[4][1]=now/(1L<<10L)%(1L<<8L);
		now_board[4][2]=now/(1L<<12L)%(1L<<10L);

		for (int j = 3; j >= 0; j--) {
			for (int k = 2; k >=0 ; k--) {
				now_board[j][k]=((now%(1L<<((j*3L+k+1L)*4L+12L)))/(1L<<((j*3L+k)*4L+12L)));
				cout<<to_bin_str(now_board[j][k])<<"  ";
			}
			cout<<endl;
		}

		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 3; k++) {
				vector<vector<vector<ll>>> now_boards(8,now_board);
				bool f[8]={};
				bool g[8]={};
				switch(now_board[j][k]){
					case 6:{//ひよこ
							   if(j+1<4){
								   if(now_board[j+1][k]<=5){
									   now_boards[0][j+1][k]=now_board[j][k];
									   now_boards[0][j][k]=0;
									   f[0]=1;
									   if(now_board[j+1][k]!=0){
										   if(now_board[j+1][k]==5){
											   g[0]=1;
										   }else{
											   now_boards[0][4][now_board[j+1][k]-1]++;
										   }
									   }
									   if(j+1==3){
										   now_boards[1]=now_board;
										   now_boards[1][j+1][k]=7;
										   f[1]=1;
										   if(g[0]){
											   g[1]=1;
										   }
									   }
								   }
							   }
							   break;
						   };
					case 10:{//ライオン
								if(j-1>=0&&k+1<3){
									if(now_board[j-1][k+1]<=5){
										now_boards[0][j-1][k+1]=now_board[j][k];
										now_boards[0][j][k]=0;
										f[0]=1;
										if(now_board[j-1][k+1]!=0){
											if(now_board[j-1][k+1]==5){
												g[0]=1;
											}else{
												now_boards[0][4][now_board[j+1][k]-1]++;
											}
										}
									}
								}
								if(j-1>=0&&k-1>=0){
									if(now_board[j-1][k-1]<=5){
										now_boards[1][j-1][k-1]=now_board[j][k];
										now_boards[1][j][k]=0;
										f[1]=1;
										if(now_board[j-1][k-1]!=0){
											if(now_board[j-1][k-1]==5){
												g[1]=1;
											}else{
												now_boards[1][4][now_board[j+1][k]-1]++;
											}
										}
									}
								}
							};
					case 7:{//にわとり
							   if(j+1<4&&k+1<3){

							   }
							   if(j+1<4&&k-1>=0){

							   }
						   };
					case 9:{//キリン
							   if(j+1<4){

							   }
							   if(j-1>=0){

							   }
							   if(k+1<3){

							   }
							   if(k-1>=0){

							   }
							   break;
						   };
					case 8:{//ぞう
							   if(j-1>=0&&k+1<3){

							   }
							   if(j-1>=0&&k-1>=0){

							   }
							   if(j+1<4&&k+1<3){

							   }
							   if(j+1<4&&k-1>=0){

							   }
							   break;
						   };
					case 0:{//持ち駒を打つ
						   
						   }
				};
				for (int l = 0; l < 8; l++) {
					if(f[l]){
						for (int m = 3; m >= 0; m--) {
							for (int n = 2; n >=0 ; n--) {
								cout<<to_bin_str(now_boards[l][m][n])<<"  ";
							}
							cout<<endl;
						}
						cout<<endl;
					}
				}	
			}
		}
	}
}
