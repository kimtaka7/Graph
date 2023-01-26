/*=======================================
** �ۼ��� : �����а� 2�г� 1�� 7�� ���°� 
** ���α׷���: ��� ���� ���� �� �м� ���α׷� 
** �Է� ��������ó : https://www.airkorea.or.kr/web/realSearch?pMENU_NO=97 
**=====================================*/ 

#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <stdlib.h> //atoi, atof �Լ� ������� 

#define days 1095 //��ü ������ ���� (�̻�) 
#define all_days 150 //���� ȸ���Ҷ� ������ ������(��) ��  
using namespace std;

void arrangement(); //����ü�� ���Ͽ��� �Է¹��� ���� �����ϴ� �Լ�
int find(char *wh_1, char *wh_2); //�Է��� ��¥�� ���� �ȿ� �����ϴ� �� Ȯ���ϰ� ��ġ�� ��ȯ�Ͽ� �ִ� �Լ�  
int file_check(); //������ ����ִ��� ������� �ʴ��� Ȯ���ϴ� �Լ� (������ 1, ������ 0 ����) 
void hold(); 

void compare();  //���ſ��� ������� �� ��� �Լ�  
int select_compare(); //���ϰ� ���� ��ü�� �Է¹ް� �Ǻ��Ͽ��ִ� �Լ�  
int percent_check(); //�������� �������� �Ǻ��ϰ� ������, ���ҷ��� ����Ͽ� �ִ� �Լ� 

void expect();  //������� ���� ��� �Լ�   
void regression(); //����ȸ���ϴ� �Լ�, �ּ� ������ 
double calcul(int a, int b); //ȸ���� ���� ����ϴ� �Լ� 

void variance(); //��ȭ�� �׷����� �׷��ִ� ��� �Լ�  
int max_check(int i); //���� �� ���� ū ���� ã�� �Լ� 
void graph(int i, int max);
void res_check();
 
void menu();
void compare_menu();
int expect_menu();
int expect_menu2(int i);
void variance_menu();


struct infor{ //����ü (���Ͽ� �ִ� �������� �����ٿ��� ����) 
	char when[15];
	int VF_dust, F_dust;
	float Ozone, NO_2, CO_2, SO_2;
};

char VF_dust[10], F_dust[10], Ozone[10], NO_2[10], CO_2[10], SO_2[10]; //�ҷ��� ���� ��� �����ϴ� ����(������, �Ǽ������� ��ȯ ��) 

infor p[days];

//wh_idx : ��¥�� �ε��� �� ������� / compare_air1 : ���� ��ü ���� ���� ���(int ��) / times : ��� �ݺ��ߴ°�?, main �Լ����� ��� 
int wh_idx[2], compare_air1[2], times; 
float compare_air2[2]; //compare_air2 : ���� ��ü ���� ���� ���(float ��)
double dx_dy; //������, ���ҷ� ����� �� ���̴� ����  
double dx_dy_2, y_intercept; //dx_dy_2 : ����ȸ�Ϳ����� ���� ���� / y_intercept : y ���� ���� 
char air_sort[20]; //���� �̸� ������� 
int value[11]; //�׷��� �׸��� ������ �����ϴ� ����  
int gaesu; //2�� ��ɿ��� ������ ���� 


int main(){
	int i = 1, j;  // i : �ݺ��� ���ǿ��� True, False ���� ��Ÿ���� ����, j : scanf �������� �����Ͱ� �������̸� 1��, �������̸� 0�� ��ȯ 
	
	//�Ҽ����� 2��°�ڸ����� �ݿø� 
	cout << fixed; 
	cout.precision(1);
	 
	if(file_check == 0){
		printf("�Է� ������ �߸� �����Ǿ��ų� ������ �ֽ��ϴ�. \n");
		hold(); //���� 
	}
	
	if(!times){ //���ʷ� ����ɶ��� ���� (�Ŀ� main�Լ��� ȣ���� �� ���Ͽ� �ִ� ������ �Ҿ���� �Ͱ� ȸ�ʹ� ���� �ѹ� �� �� �ʿ䰡 ����) 
		arrangement(); 
		regression();
		times++;
	}
	
	while(i){ //i�� 0�϶����� ���� 
		int func; //func : �Է� ���� ��ȣ�� �����ϴ� ���� 
		
		menu();
		fflush(stdin);
		j = scanf("%d", &func); // �Է��� �� func�� ����
					
		if(func == 1 && j == 1){ // 1�� �Է��ϸ� ���� 
			compare(); //��� ���� �� ����� �Լ� 
			i = 0;
		}
		else if(func == 2 && j == 1){ // 2�� �Է��ϸ� ���� 
			expect(); //��� ���� ���� ����� �Լ�  
			i = 0;
		}
		else if(func == 3 && j == 1){ // 3�� �Է��ϸ� ���� 
			variance(); //��� ���� �׷����� �׷��ִ� ����� �Լ�  
			i = 0;
		}
		else if(func == 4 && j == 1){ // 4�� �Է��ϸ� ���� 
			hold();
			i = 0;
		}
	}
	return 0; 
}


void arrangement(){
	int j = 0;
	
	FILE *pFile = NULL;
	
	//������ ���� : �ð� �ʹ̼������� �̼������� ������ �̻�ȭ���ҷ� �̻�ȭź�ҷ� �̻�ȭȲ�귮
	//ex) 2022-05-28 30 11 0.057 0.01 0.2 0.002 
	pFile = fopen("�������(2020 ~ 2022).txt", "r");
	
	while( !feof( pFile ) ){        
        fscanf(pFile, "%s %s %s %s %s %s %s\n", p[j].when, VF_dust, F_dust, Ozone, NO_2, CO_2, SO_2); //���ڿ��� �޾ƿ��� (������ ������ ���� �߻� ���ɼ� ����) 

		p[j].VF_dust = atoi(VF_dust); //int������ ��ȯ�� ����ü�� ���� 
		p[j].F_dust = atoi(F_dust);
		p[j].Ozone = atof(Ozone); //float������ ��ȯ�� ����ü�� ���� 
		p[j].NO_2 = atof(NO_2);
		p[j].CO_2 = atof(CO_2);
		p[j].SO_2 = atof(SO_2);
		
		j++;
	    }
	
	fclose(pFile);  
}


int find(char *wh_1, char *wh_2){ 
	int i = days, cnt; //i : ��ü ������ ����, cnt : ��ġ�� �ٲٱ� ���� ���� 
	
	wh_idx[0] = -1; //�ʱ갪 
	wh_idx[1] = -1;
	
	while(i >= 0){ //��� ������ �� Ž���� ������ �ݺ� 
		if(!strcmp(p[i].when, wh_1)) //���ٸ� ���� 
			wh_idx[0] = i;
		
		if(!strcmp(p[i].when, wh_2)) //���ٸ� ���� 
			wh_idx[1] = i;
		
		i--;
	}
	
	if(wh_idx[0] < wh_idx[1]){ //�������� Ư���� �̿�, ���߿� �о���� ������ �� ���� �����Ϳ��� �ε��� ���� ũ�� �� ������ ���������� Ȱ��
		//�ٲ��ִ� ���� 
		cnt = wh_idx[0]; 
		wh_idx[0] = wh_idx[1];
		wh_idx[1] = cnt;
	}
	
	if(wh_idx[0] == -1 || wh_idx[1] == -1) { //Ž���� ������ �ÿ� 
		printf("���Ͽ� �������� �ʴ� �����̰ų� ��¥ ������ �߸��Ǿ����ϴ�.");
		fflush(stdin);
		Sleep(1000); 
		return 0;
	}
	
	if(wh_idx[0] == wh_idx[1]){ //�� ���� ��¥�� �����ÿ�  
		printf("���� ��¥�� �Է��� �� �����ϴ�.");
		fflush(stdin);
		Sleep(1000); 
		return 0;
	}
	return 1; //Ž���� �������� �ÿ� 
}

int file_check(){ 
	FILE *pFile = NULL;
	
	pFile = fopen("�������(2020 ~ 2022).txt", "r"); 
	
    if( pFile == NULL ) {
		return 0;
	}
	
	fclose(pFile);
	
	return 1;	
}

void hold(){
	fflush(stdin);
	printf("\n\n");
	printf("�����Ͻ÷��� ������ Ű�� �Է��ϼ���.\n");
	getchar();
	exit(0);
}


void compare(){
	int i = 0, j = 0;  //i : �ùٸ� �̸��� �ԷµǾ����� Ȯ��, j : ���� ���� �Ǵ� �Լ� 
	char store[2][10] = {"���ҷ��� ", "�������� "}; //���� ���� ����Ҷ� ��� 
	
	compare_menu();
	
	i = select_compare(); //�ùٸ� �� �Է½� 0�� ������ �� ��ȯ, �ùٸ��� ���� �� �Է½� 0 ��ȯ
	while(!i){ //���� �ùٸ� �̸��� �Է��� �Ǿ����� �ݺ��� �ߴ� 
		printf("\n�ùٸ� ���� �Է����ּ���.\n\n\n");
		Sleep(700);
		i = select_compare();
	}
	
	if(i <= 2){ //������ �������� ��   
		printf("\n\n\n%s�� �� %s�� �� : %d ��/��\n", p[wh_idx[0]].when, air_sort, compare_air1[0]); //��¥�� �� ������ ���� ���
		printf("%s�� �� %s�� �� : %d ��/��\n\n", p[wh_idx[1]].when, air_sort, compare_air1[1]);
		
		dx_dy = (double) compare_air1[1] / compare_air1[0];
		
		j = percent_check();
	}
	else if(i > 2){ //������ �Ǽ����� ��  
		printf("\n%s�� �� %s�� �� : %.3lf ppm\n", p[wh_idx[0]].when, air_sort, compare_air2[0]); //��¥�� �� ������ ���� ���
		printf("%s�� �� %s�� �� : %.3lf ppm\n\n", p[wh_idx[1]].when, air_sort, compare_air2[1]);
		
		dx_dy = (double) compare_air2[1] / compare_air2[0];			
	
		j = percent_check();
	}
	
	//ex) '�ʹ̼������� �������� 35.1 % �Դϴ�.'  
	cout << air_sort;
	cout << "�� ";
	cout << store[j];
	cout << dx_dy;
	cout << " % �Դϴ�.";
	Sleep(700);
	
	res_check();
}

int select_compare(){
	printf("*������ �� �ִ� �� : �ʹ̼�����, �̼�����, ����, �̻�ȭ����, �̻�ȭź��, �̻�ȭȲ��");
	printf("\n\n��� ���� �������� �Է��Ͽ� �ּ��� : ");
	
	fflush(stdin);
	scanf("%s", air_sort);
	
	if(!strcmp(air_sort, "�ʹ̼�����")){ //'�ʹ̼�����'�� �ԷµǾ��� ��  
		compare_air1[0] = p[wh_idx[0]].VF_dust;
		compare_air1[1] = p[wh_idx[1]].VF_dust;
		return 1; 
	}	
	else if(!strcmp(air_sort, "�̼�����")){ //'�̼�����'�� �ԷµǾ��� �� 
		compare_air1[0] = p[wh_idx[0]].F_dust;
		compare_air1[1] = p[wh_idx[1]].F_dust;
		return 2;
	}	
	else if(!strcmp(air_sort, "����")){ //'����'�� �ԷµǾ��� �� 
		compare_air2[0] = p[wh_idx[0]].Ozone;
		compare_air2[1] = p[wh_idx[1]].Ozone;
		return 3; 
	}	
	else if(!strcmp(air_sort, "�̻�ȭ����")){ //'�̻�ȭ����'�� �ԷµǾ��� �� 
		compare_air2[0] = p[wh_idx[0]].NO_2;
		compare_air2[1] = p[wh_idx[1]].NO_2;
		return 4;
	}	
	else if(!strcmp(air_sort, "�̻�ȭź��")){ //'�̻�ȭź��'�� �ԷµǾ��� �� 
		compare_air2[0] = p[wh_idx[0]].CO_2;
		compare_air2[1] = p[wh_idx[1]].CO_2;
		return 5;
	}	
	else if(!strcmp(air_sort, "�̻�ȭȲ��")){ //'�̻�ȭȲ��'�� �ԷµǾ��� �� 
		compare_air2[0] = p[wh_idx[0]].SO_2;
		compare_air2[1] = p[wh_idx[1]].SO_2;
		return 6;
	}
	return 0;
}

int percent_check(){
	if(dx_dy > 1){ // (������ ��/������ ��)�� 1�� ���� ��, �� ���� ������ ��  
		//�ۼ�Ʈ�� ��ȯ  
		dx_dy = (double) dx_dy - 1;
		dx_dy *= 100;
		return 1;
	}	
	else{ // (������ ��/������ ��)�� 1�� ���� ���� ��, �� ���� ������ ��  
		dx_dy = (double) 1 - dx_dy;
		dx_dy *= 100;
		return 0;
	}
}


void expect(){	
	int i = 0, max = 0; //i : �ݺ� Ȯ�� �� � ��ü�� �����ϴ��� Ȯ���ϴ� ����, max : �ִ� 
	double result = 0; //�ᱣ���� �����ϴ� ���� 
	
	while(!i) //i�� 0�� �ƴҶ� ���� �ݺ� 
		i = expect_menu(); //i = 0 -> �߸��� �� �Է�, i = 1 -> �ʹ̼����� �� ����, i = 2 -> �̼����� �� ����
	
	expect_menu2(i); 
	
	max = max_check(0); //max_check�� 0�� �־��ָ� �ִ񰪸� ���� �� ���� 
	graph(0, max); //3�� ��ɰ� �и��ؾ� �Ǳ⿡ 0�� �־��� 
	
	res_check();
}

void regression(){
	//avg_F : �̼������� ���, avg_VF : �ʹ̼������� ���, x_xavg : x-x���, y_yvg : y-y��� 
	double avg_F = 0, avg_VF = 0, x_xavg, y_yavg, x_y_avg = 0, x_x_avg = 0; // x_y_avg : ��(x-x���)(y-y���) , x_x_avg : ��(x-x���)^2
	int all_F = 0, all_VF = 0, i; //all_f : ��� �̼������� ��, all_VF : ��� �ʹ̼������� �� 
	
	for(i = 0; i < all_days; i++){ //��� �̼�����&�ʹ̼������� ���� ���ϴ� ���� 
		all_VF += p[i].VF_dust;
		all_F += p[i].F_dust;
	}
	
	avg_F = (double) all_F / all_days;
	avg_VF = (double) all_VF / all_days;
	
	for(i = 0; i < all_days; i++){
		x_xavg =  (double) p[i].VF_dust - avg_VF;
		y_yavg = (double) p[i].F_dust - avg_F;
		
		x_y_avg += (double) x_xavg * y_yavg;
		x_x_avg += (double) x_xavg * x_xavg;
	}
	
	dx_dy_2 = x_y_avg / x_x_avg; //�ּ����������� ���� 
	y_intercept = (double) avg_F - (avg_VF * dx_dy_2); //�ּ����������� y���� 
}

double calcul(int i, int k){ //i = 1�̸� �ʹ̼����� �� ���ϱ� i = 2�̸� �̼����� �� ���ϱ�, k : �Էµ� ��
	// * y = ax + b���� y ���� �̼�����, x ���� �ʹ̼�����  
	double result = 0;
	
	if(i == 1){ // x = (y - b)/a
		result = (double) (k - y_intercept)/dx_dy_2;
		return result;
	}
	else{ // y = ax + b
		result = (double) dx_dy_2 * k + y_intercept;
		return result;
	}
}


void variance(){
	int i = 0;
	int max = 0; //�ִ��� �����ϴ� ���� 
	
	variance_menu();
	
	if(abs(wh_idx[0] - wh_idx[1]) >= 10){ //�� ���� �ε����� ���� 10�� ���� ��� (�׷����� �ʹ� �¿�� ������� ������) 
		printf("�� ��¥�� ���̰� 10�� ���� �ʵ��� ���ּ���.");
		Sleep(1000);
		variance_menu();
	}
	
	i = select_compare();
	
	while(!i){ //���� �ùٸ� �̸��� �Է��� �Ǿ����� �ݺ��� �ߴ� 
		printf("\n\n�ùٸ� �̸��� �Է����ּ���.\n\n");
		Sleep(1000); 
		i = select_compare();  //�ٽ� ȣ�� 
	}
	
	max = max_check(i);
	graph(i, max);
	Sleep(1000);
	
	res_check();
}

int max_check(int i){ 
	int j = 0, k = wh_idx[0], max = 0;
	double cnt;
	
	while(j <= 10){
		if(i == 1){ //�ʹ̼������� ����� ��  
			value[j] = p[k].VF_dust * 100;
			k--;
		}
		else if(i == 2){ //�̼������� ����� �� 
			value[j] = p[k].F_dust * 100;
			k--;
		}
		else if(i == 3){ //������ ����� �� 
			cnt = p[k].Ozone * 100000;
			value[j] = (int) cnt;
			k--;
		}
		else if(i == 4){ //�̻�ȭ���Ҹ� ����� �� 
			cnt = p[k].NO_2 * 100000;
			value[j] = (int) cnt;
			k--;
		}
		else if(i == 5){ //�̻�ȭź�Ҹ� ����� �� 
			cnt = p[k].CO_2 * 100000;
			value[j] = (int) cnt;
			k--;
		}
		else if(i == 6){ //�̻�ȭȲ���� ����� �� 
			cnt = p[k].SO_2 * 100000;
			value[j] = (int) cnt;
			k--;
		}
		if(k < wh_idx[1]) //��� ��¥ ������ �� �о��� ��  
			break;
			
		if(max < value[j]) //max �ʱ�ȭ 
			max = value[j];
			
		j++;
	}	
	return max;
}

void graph(int i, int max){ //�׷����� 25ĭ���� ����� ����ϱ� ������ �ϳ��� ������ �׷����� ���� -> ������ �ؼ� �׷����� �׷��� 
	//maxx : �׷������� ���� ��Ÿ�� �� �࿡�� ���� ū ��(������ �Ǵ� ��), max_x = maxx, s_unit : ���� 1ĭ, unit : 5ĭ(�࿡�� ���� ��Ÿ�� ��) 
	//c_unit : �׷��� �׸� �� ����ϴ� ����, num_in : ��ġ�� �����ϴ� ���� 
	//len : ������ ����, k/j : �ݺ����� ����ϱ� ���� ����, x : 0�̸� ppm��, 1�̸� ��/����
	//store : ������ �����ϴ� ����, storage : �������� �����Ҷ� ��Ʈ���� ����� �޾ƿ��� ���� ����
	int maxx = 0, max_x, unit, s_unit, c_unit = 0;
	int num_in, lens = wh_idx[0] - wh_idx[1] + 1;
	int k, j, x = 0, y[2] = {100,100000}, z[2] = {0, 2};
	double storage = 0;
	char store[2][10] = {"ppm", "��/��"};
	
	if(i > 2){
		x = 1; //�Ҽ��� �ڸ��� ���߱� (3�ڸ�) 
		cout << fixed; 
		cout.precision(3);
	}
	if(i == 0) lens = gaesu; //2�� ��ɿ��� �׷����� �Ѿ�� ��  
	
	maxx = max + (1000 - (max % 1000)); //�࿡�� �ִ� ��� 
	
	unit = maxx/5;
	s_unit = maxx/25; //���� ���� ������ 25�� ����� ����� 
	max_x = maxx;
	
	system("mode con cols=170 lines=40");
	
	cout.width(85);
	cout << air_sort;
	
	printf("\n\n");
	
	//���� ǥ��  
	cout << "���� : "; 
	cout.width(5);
	cout << store[x] << endl << endl; 
	
	//�׷��� �׸��� ���� 
	for (k = 25; k > 0; k--) {
		if(k % 5 == 0){ //5ĭ���� ���� ���� �� ǥ��  
			cout.width(12);
			storage = (double) maxx/y[x];
			cout << storage;
			cout.width(2);
			cout << "��";
			maxx -= unit;
		}
		else{ //���� ���� ��  
			cout.width(14);
			cout << "��";
		}
		
		for (j = 0; j < lens; j++) {
			num_in = value[j]; //���� ����� �׷��ߵǴ� �� 
			int p = max_x - c_unit; //��ĭ�� �������鼭 p ���� ������ ex) �ִ��� 250�̶�� p�� 250, 240, 230, 220, 210 ... 0 �̷��� �ٲ�
			  
			if (num_in >= p) {  
				if (num_in - p >= 0 && num_in - p < s_unit) { //�� - p ���� 0�̻�, ���� ���� ���� �̸� 
					cout.width(16);
				 	cout << "����"; //������ ǥ���ϴ� ���� ��ȣ ���
				 }  
				else { 
					cout.width(16);
					cout << "����"; // ���� ��ȣ ���
				}  
			}
			else { //���븦 ����ߵǴ� ���  
				cout.width(14);
				cout << "";
			}
		}
		c_unit += s_unit;
		cout << endl;
	}
	
	cout.width(12);
	cout << 0; //�࿡�� 0
	 
	cout.width(1);
	cout << "������������";
	
	for (k = 0; k < lens; k++) {
		if (value[k] != 0) cout << "���������������ئئ���������"; //���� 0�̾ƴ� ���� �����Ѵٸ�  
		else cout << "����������������������������"; //���� 0�̶�� 
	}
	cout << "��������>" << endl;
	
	cout.width(17);
	cout << "";
	
	for (k = 0; k < lens; k++) {
		if(i == 0) break; //2�� ��ɿ��� �׷����� �׸��� ��¥�� ǥ���� �ʿ䰡 ���� 
		cout.width(14);
		cout << p[wh_idx[0] - k].when; //��¥ ��� 
	}
	printf("\n");
	
	cout.width (15+z[x]); //z������ �� ���� : �׷����� ���ڰ� �׸������� �鿩���⸦ ������ 
	cout << "���� ��:";
	
	for (k = 0; k < lens; k++) {
		cout.width(11-z[x]); //���� ������ ���� 
		storage = (double) value[k]/y[x]; 
		cout << storage; //���� �� 
		cout << store[x]; //����  
	}
}

void res_check(){
	char i[10];
	
	printf("\n\n\n\n");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //��������� ����  
	printf("�ٸ� ��� ��� - 1��\n");
	printf("���α׷� ���� 2��\n\n");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //������� ����  
	printf("���� �Է����ּ��� : "); 
	fflush(stdin);
	scanf("%s",  i);
	
	if(i[0] == '1' && i[1] == '\0'){ // 1�� �Է��ϸ� ���� 
		main();
		return;
	}	
	else if(i[0] == '2' && i[1] == '\0'){ // 2�� �Է��ϸ� ���� 
		hold();
		return;
	}
	
	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("�ùٸ� ���� �Է����ּ���.");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	
	Sleep(1000);
	res_check(); //���(�ùٸ��� ���� ���� �ԷµǾ��� ����) 
} 


void menu(){
	system("mode con cols=80 lines=35"); //�ܼ�â ũ�� ���� - ĭ(cols):80, ��(lines):35
	
	printf("* �� ���α׷��� ���̽� ������ �������� �����Ͽ����ϴ�.\n");
	printf("* 2020-01-01���� 2022-05-31������ ���� �����մϴ�.\n\n\n");
	
	printf("===================================================\n");
	printf("             ��� ���� �м� ���α׷�               \n");
	printf("===================================================\n\n\n"); 
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // �۾� �ʷϻ� 

	printf("���� ��� �� ����ϰ� ���� ����� ��ȣ�� �Է��� �ּ���\n\n"); 
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // �۾� ���

	printf("1. ���ſ��� ��� ������ ��\n");
	printf("2. �̷� ��� ���� ����\n"); 
	printf("3. ���� ��¥ ���̿� ���� ��ü�� ��ȭ�� �׷���\n");
	printf("4. ���α׷� ����\n\n\n");
	
	printf("��� �ϰ� ���� ��� : ");
}

void compare_menu(){
	char wh_1[15], wh_2[15]; //��¥�� �޾Ƶ��̴� �迭 
	int check; //��¥�� �� �ԷµǾ����� 1, �� �Էµ��� �ʾ����� 0�� �����ϴ� ���� 
	
	system("mode con cols=90 lines=30");
	
	printf("\n=============================================================\n");
	printf("                   ���ſ��� ��� ���� ��                   \n");
	printf("=============================================================\n\n\n");
	
	printf("���ϰ� ���� ��¥�� ����-��-�� ������ �Է��� �ּ���\n");
	printf("ex) 2020�� 6�� 1�� -> 2020-06-01\n\n\n");
	fflush(stdin);
	
	printf("��¥�� �Է��Ͽ� �ּ��� : ");
	scanf("%s", wh_1);
	printf("���ϰ� ���� ��¥�� �Է��Ͽ� �ּ��� : " );
	scanf("%s", wh_2);
	printf("\n\n");
	
	check = find(wh_1, wh_2); 
	
	if(!check) //��¥�� �ùٸ��� ã������ �ʾ��� ��� 
		compare_menu();
} 

int expect_menu(){
	int func, i; //func : �Է� ���� ��ȣ�� �����ϴ� ����
	
	system("mode con cols=80 lines=30");

	printf("*���� �ܺ� ������ ���� �ޱ� ������ ��Ȯ���� ���� ���� �ֽ��ϴ�.\n");
	printf("*�ʹ̼������� �̼������� ���ؼ��� �� ����� �����մϴ�.\n\n\n");
		
	printf("=============================================================\n");
	printf("                        ��� ���� ����                       \n");
	printf("=============================================================\n\n\n");
	
	printf("�ʹ̼������� �̼������� ������ �Է½�Ű�� �������ִ� ����Դϴ�.\n\n");
	printf("�ʹ̼������� �����ϰ� ������ 1��, \n�̼������� �����ϰ� ������ 2���� �Է����ּ���.\n\n\n");
	
	printf("���� �Է��Ͽ� �ּ��� : ");
	fflush(stdin);
	i = scanf("%d", &func); 
	
	if(func == 1 && i == 1) return 1; //���� ���� 1�϶�  
	if(func == 2 && i == 1) return 2; //���� ���� 2�϶�
	
	printf("\n1 �Ǵ� 2�� �Է����ּ���");
	Sleep(800);
}

int expect_menu2(int i){
	//cal : ������ �޾ƿ��� ����, n : ������ �޾ƿ��� ����, p : ó������ ���ڿ����� �������� �Ǵ�, �Ŀ� �ε��� ������ Ȱ�� 
	//q : �������� ���ڿ����� �Ǵ�  
	int cal, n, p, q;
	double result;
	
	system("mode con cols=65 lines=30");
	
	do{
		printf("�����ϰ� ���� �������� ����(�ִ� 10)�� �Է����ּ���\n");
		printf("-->");
		fflush(stdin);
		p = scanf("%d",&n); //���ڿ��� �ԷµǸ� p = 0, ���ڰ� �ԷµǸ� p = 1 
		if(n > 10)
			p = 0;
	}
	while(!p);
	
	gaesu = n; 
	p = 0; //�ؿ� value �迭�� ������� �� �ε��� ������ Ȱ���ϱ� ����  
	
	printf("*���ǻ��� : ���� ���̰� �ʹ� ũ�� �׷����� �̻��ϰ� �׷�����!");
	printf("*�Ҽ����� �ν��� ���� �ʽ��ϴ�.\n\n"); 
	
	while(n > 0){
		if(i == 1){ //1�϶� ��, �ռ� ������ �ʹ̼������� �������� ��   
			printf("%d��° �̼����� ��(ppm)�� �Է����ּ��� : ",p+1); 
			
			fflush(stdin);
			q = scanf("%d", &cal);
			
			strcpy(air_sort, "�ʹ̼�����"); 
			
			if(cal < 5 || cal >= 1500 || q == 0){ //q = 0 : ���ڿ��� �ԷµǾ��� ��  
				printf("\n");
				printf("5ppm �̻� 1500ppm �̸��� ���� �Է��Ͽ� �ּ���\n\n"); 
				Sleep(1000);
				continue;
			}
		}
		else{ //�׿ܿ� ��Ȳ(i�� 2�϶�) 
			printf("%d��° �ʹ̼����� ��(ppm)�� �Է����ּ��� : ",p+1); 
			
			fflush(stdin);
			q = scanf("%d", &cal);
			
			strcpy(air_sort, "�̼�����"); 
			
			if(cal < 5 || cal >= 1500 || q == 0){
				printf("\n");
				printf("5ppm �̻� 1500ppm �̸��� ���� �Է��Ͽ� �ּ���\n\n"); 
				Sleep(1000);
				continue;
			}
		}
		result = calcul(i, cal); //���� �޾ƿ��� �� ���� �������� ȸ�ͺм� 
		value[p] = (int) result * 100; //100�� ���ؼ� ���� 
		p++;
		n--;
	}
}

void variance_menu(){
	char wh_1[15], wh_2[15]; //��¥�� �޾Ƶ��̴� �迭 
	int check; //��¥�� �� �ԷµǾ����� 1, �� �Էµ��� �ʾ����� 0�� �����ϴ� ����
	
	system("mode con cols=80 lines=30");
	
	printf("*�� ��¥�� ���̰� 10���� ���� �ʵ��� ���ּ���.\n\n\n");
	
	printf("\n=============================================================\n");
	printf("            ���� ��¥ ���̿� ������� ��ȭ�� �׷���        \n");
	printf("=============================================================\n\n\n");
	
	printf("��¥ 2���� ��ü�� �Է��ϸ� ��� ���� ��ȭ���� �����ִ� ����Դϴ�.\n\n"); 
	printf("���ϰ� ���� ��¥�� ����-��-�� ������ �Է��� �ּ���\n");
	printf("ex) 2020�� 6�� 1�� -> 2020-06-01\n\n\n");
	
	printf("��¥�� �Է��Ͽ� �ּ��� : ");
	scanf("%s", wh_1);
	printf("�ι��� ��¥�� �Է��Ͽ� �ּ��� : " );
	scanf("%s", wh_2);
	printf("\n\n");
	
	check = find(wh_1, wh_2); 
	
	if(!check) //��¥�� �ùٸ��� ã������ �ʾ��� ��� 
		variance_menu();
} 
