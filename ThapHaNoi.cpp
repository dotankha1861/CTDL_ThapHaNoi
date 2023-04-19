#include <iostream>
#include "console.h"
#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_Enter   13
#define key_Esc     27
#define key_F1      2059
#define soDiaToiDa  20 
int speed = 5, chieuCaoCot, chieuDaiCot;
int reset = false;
using namespace std;
struct Dia{
	int mau;
	int cot;
	int dong;
	int chieuDai;	
};
struct Cot{
	Dia nDia[soDiaToiDa];
	int slDia;
	char ten;	
};
Cot nCot[3];
int Key(){
	int key=getch();
	if (key==224){
		key=getch();
		return key+1000;
	}
	if(key==0){
		key=getch();
		return key+2000;
	} 
	return key;
}
void Pause(){
	while(1) if(_kbhit()){
		Key();
		break;
	}
}
void setTocDo(int key){
	if(key==key_Up){
		if(speed==9) speed=1;
		else speed++;
	} 
	else{
		if(speed==1) speed=9;
		else speed--; 
	}
	gotoXY(32,1);
	setBGColor(ColorCode_Black);
    cout<<speed;
}
void Xoa(){
	for(int i=0; i<=chieuCaoCot+2;i++) {
		gotoXY(0,4+i);		
		setBGColor(ColorCode_Black);
		for(int i=0;i<(chieuDaiCot+2)*3;i++) cout<<" ";
	}
}
void nhapSoDia(int& soDia){
	int key;
	while(1){
		setBGColor(ColorCode_Black);
		gotoXY(30,2); 
		clreol();
		if(soDia!=0) cout<<soDia;
		while(1) if(_kbhit()) break; 
		key=Key();
		if(key<='9'&&key>='0') soDia = soDia*10 + key-'0';
		else if(key==key_F1) soDia/=10;
		else if(key==key_Up||key==key_Down) setTocDo(key);
		else if(key==key_Enter) if(soDia!=0) return;
		if(soDia>20) soDia=20;
	}
}
void veDia(Dia dia){
	setBGColor(dia.mau);
	gotoXY(dia.cot,dia.dong);
	for(int n=0;n<dia.chieuDai;n++) cout<<" ";
}
void xoaDia(Dia dia){
	setBGColor(ColorCode_Black);
	gotoXY(dia.cot,dia.dong);
	for(int n=0;n<dia.chieuDai;n++) cout<<" ";
}
void ve3cot(){
    for(int i=0;i<=2;i++){ 
		gotoXY(i*(2+chieuDaiCot)+2,chieuCaoCot+6);
		setBGColor(ColorCode_White);
		for(int k=0;k<chieuDaiCot;k++) cout<<" ";
		gotoXY(3+i*(chieuDaiCot+2)+chieuDaiCot/2, chieuCaoCot+6);
		for(int j=1;j<=chieuCaoCot;j++){
			gotoXY(whereX()-1,whereY()-1);
			cout<<" ";
		}
	}
}
void venDia(int slDia){
	for(int m=0;m<slDia;m++){
		nCot[0].nDia[m].dong = chieuCaoCot + 6 - (m+1);
		nCot[0].nDia[m].cot = 2 + (m+1) ;
		nCot[0].nDia[m].chieuDai = chieuDaiCot - 2*(m+1); 
		nCot[0].nDia[m].mau = m%14+1;
		veDia(nCot[0].nDia[m]);
	}
}
void khoiTaoCot(int soDia){
	nCot[0].slDia = soDia;
	nCot[1].slDia = nCot[2].slDia = 0;
	chieuCaoCot = soDia + 2;
    chieuDaiCot = 3 + soDia*2;	 
	for(int i=0;i<=2;i++)  nCot[i].ten = 'A' +i; 
	ve3cot();
	venDia(soDia);
}
void Menu(){
	char* thaotac[2]={(char*)"  Co   ",(char*)" Khong "};
	int tt =0;
	gotoXY(1,chieuCaoCot+8);
	setBGColor(0);
	cout<<" Dung han ? ";
	int key;
	int mau[2];
	while(1){
		for(int i=0;i<2;i++) mau[i]= ColorCode_DarkRed;
		mau[tt] = ColorCode_Green;
		gotoXY(15,chieuCaoCot+8);
		for(int i=0;i<2;i++){
			setBGColor(mau[i]);
			cout<<thaotac[i];
		}
		if(kbhit()){
			key=Key();
			if(key==key_Left||key==key_Right){
				if(tt==0) tt=1;
				else tt=0;
			} 
			if(key==key_Enter) {
				gotoXY(1,chieuCaoCot+8);
				setBGColor(ColorCode_Black);
				cout<<"                                 ";
				if(tt==0){
					Xoa();
					reset=true;
				}
				return;
			}
		}	
	}
}
int kiemTraPhim(int& reset){
	int key=Key();
	if(key==key_Up||key==key_Down) setTocDo(key);
    else if(key==key_Esc) Menu();
	else if(key==key_F1){
		gotoXY(2,chieuCaoCot+8);
	    setBGColor(ColorCode_Black);
	    cout<<"Nhan phim bat ki de tiep tuc ";
	    Pause();
	    gotoXY(2,chieuCaoCot+8);
	    clreol();
	} 
}	
void chuyenDia(Cot& cotDau,Cot& cotCuoi){
	while(cotDau.nDia[cotDau.slDia-1].dong>4){
		Sleep(50+(5-speed)*10);
		if(_kbhit()) kiemTraPhim(reset);
		if(reset) return;
	    xoaDia(cotDau.nDia[cotDau.slDia-1]);
	    if(cotDau.nDia[cotDau.slDia-1].dong>5){
		    	gotoXY(cotDau.nDia[cotDau.slDia-1].cot
				+ cotDau.nDia[cotDau.slDia-1].chieuDai/2,whereY());
				setBGColor(ColorCode_White);
				cout<<" ";
		}
	    cotDau.nDia[cotDau.slDia-1].dong--;
	    veDia(cotDau.nDia[cotDau.slDia-1]);
	}
	int t = cotDau.ten - cotCuoi.ten;
	int xtam = whereX()-cotDau.nDia[cotDau.slDia-1].chieuDai;
	if(t<0){
		t*=-1;
		while(cotDau.nDia[cotDau.slDia-1].cot != xtam+(chieuDaiCot+2)*t){
			if(_kbhit()) kiemTraPhim(reset);
			if(reset) return;
			Sleep(50+(5-speed)*10);
		    xoaDia(cotDau.nDia[cotDau.slDia-1]);
		    cotDau.nDia[cotDau.slDia-1].cot++;
		    veDia(cotDau.nDia[cotDau.slDia-1]);
		}
	}
	else{
		while(cotDau.nDia[cotDau.slDia-1].cot!=xtam-(chieuDaiCot+2)*t){
			Sleep(50+(5-speed)*10);
			if(_kbhit()) kiemTraPhim(reset);
			if(reset) return; 
		    xoaDia(cotDau.nDia[cotDau.slDia-1]);
		    cotDau.nDia[cotDau.slDia-1].cot--;
		    veDia(cotDau.nDia[cotDau.slDia-1]);
		}
	}
	while(cotDau.nDia[cotDau.slDia-1].dong<5+(chieuCaoCot-cotCuoi.slDia)){
		Sleep(50+(5-speed)*10);
		if(_kbhit()) kiemTraPhim(reset);
		if(reset) return;
	    xoaDia(cotDau.nDia[cotDau.slDia-1]);
        if(cotDau.nDia[cotDau.slDia-1].dong>5){
		    	gotoXY(cotDau.nDia[cotDau.slDia-1].cot
				+ cotDau.nDia[cotDau.slDia-1].chieuDai/2,whereY());
				setBGColor(ColorCode_White);
				cout<<" ";
		}
		cotDau.nDia[cotDau.slDia-1].dong++;	
	    veDia(cotDau.nDia[cotDau.slDia-1]);
	}
	cotCuoi.slDia++;
	cotCuoi.nDia[cotCuoi.slDia-1]=cotDau.nDia[cotDau.slDia-1];
	cotDau.slDia--;
}
void thapHaNoi(int soDia, Cot& cotDau, Cot& cotTG, Cot& cotCuoi){
	if(reset) return;
	if(soDia==1) chuyenDia(cotDau, cotCuoi);
	else{
		thapHaNoi(soDia-1, cotDau, cotCuoi, cotTG);
		chuyenDia(cotDau, cotCuoi);
		thapHaNoi(soDia-1, cotTG, cotDau, cotCuoi);
	}
}
int main(){
	int soDia;
	cout<<endl<<"  Toc do di chuyen dia ( 1-9 ): "<<speed<<endl;
	cout<<"  So dia can chuyen ( 1-20 ): ";
	gotoXY(0,0);
	cout<<"  | ^ : tang toc do | v : giam toc do";
	cout<<"| F1 : tam dung| Esc :dung han |";
	while(1){
		soDia = 0;
		setCursor(1,1);
	    nhapSoDia(soDia);
	    setCursor(0,0);
	    khoiTaoCot(soDia);
	    gotoXY(2,chieuCaoCot+8);
	    setBGColor(ColorCode_Black);
	    cout<<"Nhan phim bat ki de bat dau ";
	    Pause();
	    gotoXY(2,chieuCaoCot+8);
		clreol();
	    thapHaNoi(soDia,nCot[0],nCot[1],nCot[2]);
	    if(reset){
	    	reset=false;
	    	continue;
		}
	    gotoXY(2,chieuCaoCot+8);
	    setBGColor(ColorCode_Black);
	    cout<<"Nhan phim bat ki de quay lai tu dau ";
	    Pause();
	    gotoXY(2,chieuCaoCot+8);
		clreol();
		Xoa();  
    }
}
