
#include "stdlib.h"
#include "stdio.h"
#include<string.h>
#include <time.h>
#include<math.h>
#include <unistd.h>

typedef struct {
	char *instruccion;
	int PCValue;
}instrucciones;

instrucciones *inst; 			//Vector 

//Variables globales
int cont=0;
int pc=0;  							// indice para PC
char numeroBin[32]={};
int BancoRegistros[32];
int Stack[469753855];
char opcode[6];
char function[6];
int rs, rt, rd;
int shamt;
int immediate;
int addres;

void  PC(){
	int value=0x00400000;
	inst[0].PCValue= value;
	for(int i =1; i<(cont-1); i++){
			inst[i].PCValue= inst[i-1].PCValue +0x04;	
	}
	
}

void vaciarnumeroBin(char temporal[]){
	int i;
	for (i =0; i<32; i++){
		temporal[i] = '\0';
	}
}
void vaciar(char temporal[]){
	int i;
	for (i =0; i<11; i++){
		temporal[i] = '\0';
	}
}

void copiar (char temp[], int i){
	int N= strlen(temp)+1;
	inst[i].instruccion=(char*)malloc(N*sizeof(char));
	if(inst[i].instruccion ==NULL){
		printf("No se pudo acceder a memoria"),
		exit(1);
	}
	strcpy(inst[i].instruccion, temp);
}

void decodificador_binario(char numeroHex[]){
	char c=0;
	int i=0;
		
	
	for(int j=0; j<8; j++){
		c= numeroHex[j];
		if(i<32){	
			if(c == '0'){
				numeroBin[i]='0';
				numeroBin[i+1]='0';
				numeroBin[i+2]='0';
				numeroBin[i+3]='0';
				
			}
			else if(c == '1'){
				numeroBin[i]='0';
				numeroBin[i+1]='0';
				numeroBin[i+2]='0';
				numeroBin[i+3]='1';
				
			}
			else if(c == '2'){
				numeroBin[i]='0';
				numeroBin[i+1]='0';
				numeroBin[i+2]='1';
				numeroBin[i+3]='0';

			}
			else if(c == '3'){
				numeroBin[i]='0';
				numeroBin[i+1]='0';
				numeroBin[i+2]='1';
				numeroBin[i+3]='1';
			}

			else if(c == '4'){
				numeroBin[i]='0';
				numeroBin[i+1]='1';
				numeroBin[i+2]='0';
				numeroBin[i+3]='0';

			}
			else if(c == '5'){
				numeroBin[i]='0';
				numeroBin[i+1]='1';
				numeroBin[i+2]='0';
				numeroBin[i+3]='1';

			}
			else if(c == '6'){
				numeroBin[i]='0';
				numeroBin[i+1]='1';
				numeroBin[i+2]='1';
				numeroBin[i+3]='0';
			}
			else if(c == '7'){
				numeroBin[i]='0';
				numeroBin[i+1]='1';
				numeroBin[i+2]='1';
				numeroBin[i+3]='1';
			}
			else if(c == '8'){
				numeroBin[i]='1';
				numeroBin[i+1]='0';
				numeroBin[i+2]='0';
				numeroBin[i+3]='0';
			}
			else if(c == '9'){
				numeroBin[i]='1';
				numeroBin[i+1]='0';
				numeroBin[i+2]='0';
				numeroBin[i+3]='1';
				
			}
			else if(c == 'a'){
				numeroBin[i]='1';
				numeroBin[i+1]='0';
				numeroBin[i+2]='1';
				numeroBin[i+3]='0';
				
			}
			else if(c == 'b'){
				numeroBin[i]='1';
				numeroBin[i+1]='0';
				numeroBin[i+2]='1';
				numeroBin[i+3]='1';
				
			}
			else if(c == 'c'){
				numeroBin[i]='1';
				numeroBin[i+1]='1';
				numeroBin[i+2]='0';
				numeroBin[i+3]='0';
			
			}
			else if(c == 'd'){
				numeroBin[i]='1';
				numeroBin[i+1]='1';
				numeroBin[i+2]='0';
				numeroBin[i+3]='1';
				
			}
			else if(c == 'e'){
				numeroBin[i]='1';
				numeroBin[i+1]='1';
				numeroBin[i+2]='1';
				numeroBin[i+3]='0';
				
			}
			else if(c == 'f'){
				numeroBin[i]='1';
				numeroBin[i+1]='1';
				numeroBin[i+2]='1';
				numeroBin[i+3]='1';
				
			}
			i = i+4;
		}
	}
	//printf("%s \n", numeroBin);
}
void Guardarfichero(){

	int i;
	char temporal[11];
	char tempBinario[31];
	

	FILE *f;

	f = fopen("Pruebalw.txt", "r");
	if (f == NULL){
		printf("No se ha podido abrir el fichero.\n");
		exit(1);
	}
	
	while(!feof(f)){
		fgets(temporal, 11, f);
		cont++;
	}

	rewind(f);

	inst = (instrucciones*)malloc(cont*sizeof(instrucciones));
	if (inst == NULL){
		printf("No se ha podido reservar la memoria. \n");
		exit(1);
	
	}

	for ( i=0; !feof(f)  ; i++){
		vaciar(temporal);
		fgets(temporal, 11, f);
		decodificador_binario(temporal);
		copiar(numeroBin , i);
		vaciarnumeroBin(numeroBin);
	}

}

void prueba(){
	char x[10];
	
	strcpy( x , inst[1].instruccion);
	printf("%c", x[7]);

}

int decoBinDecimal(char NumBin[]){                  ////// Decodificador para numeros de 5 bits
	int suma=0;
	
	for(int i=0; i<5; i++){
		if(NumBin[i]=='1'){
			if(i==4)
				suma=suma+1;
			else if(i==3)
				suma=suma+2;
			else if(i==2)
				suma=suma+4;
			else if(i==1)
				suma=suma+8;
			else if(i==0)
				suma=suma+16;		
		}
	}
	
	return(suma);
}
int decoBinDecimal2Signo(char NumBin[]){        /////decodificador para numeros de 16 bits con bit reservado para signo
	 int suma=0;
	char temp[16];
	
	if(NumBin[0]=='1'){  //// invierte el numero para calcular el valor con signo (complemento a 1)
		for(int j=0; j<16; j++){
			if (NumBin[j]=='1'){
				temp[j]='0';
			}
			else  if (NumBin[j]=='0'){
				temp[j]='1';
			}
		}
		
	}
	else 
		strcpy(temp, NumBin);
	
	for(int i=1; i<16; i++){
		if(temp[i]=='1'){
			if(i==15)
				suma=suma+1;
			else if(i==14)
				suma=suma+2;
			else if(i==13)
				suma=suma+4;
			else if(i==12)
				suma=suma+8;
			else if(i==11)
				suma=suma+16;
			else if(i==10)
				suma=suma+32;
			else if(i==9)
				suma=suma+64;
			else if(i==8)
				suma=suma+128;
			else if(i==7)
				suma=suma+256;
			else if(i==6)
				suma=suma+512;
			else if(i==5)
				suma=suma+1024;
			else if(i==4)
				suma=suma+2048;
			else if(i==3)
				suma=suma+4096;
			else if(i==2)
				suma=suma+8192;
			else if(i==1)
				suma=suma+16384;
		}
	}
	if (NumBin[0]=='1'){
		suma=suma+1;  					//// le suma 1 para realizar el complemento a 2.
		suma=-1*suma;						//// para agregar el signo lo multiplica por -1.
		
	}
	return(suma);
 }
int decoBinDecimal2Unsigned(char NumBin[]){  /////decodificador para numeros de 16 bits sin  bit reservado para signo
	 int suma=0;
	
	for(int i=0; i<16; i++){
		if(NumBin[i]=='1'){
			if(i==15)
				suma=suma+1;
			else if(i==14)
				suma=suma+2;
			else if(i==13)
				suma=suma+4;
			else if(i==12)
				suma=suma+8;
			else if(i==11)
				suma=suma+16;
			else if(i==10)
				suma=suma+32;
			else if(i==9)
				suma=suma+64;
			else if(i==8)
				suma=suma+128;
			else if(i==7)
				suma=suma+256;
			else if(i==6)
				suma=suma+512;
			else if(i==5)
				suma=suma+1024;
			else if(i==4)
				suma=suma+2048;
			else if(i==3)
				suma=suma+4096;
			else if(i==1)
				suma=suma+8192;
			else if(i==0)
				suma=suma +16384;
		}
	}	
	return(suma);
 }
int decoBinDeci_32bt(char NumBin[]){
	int suma=0;
	int j=31;
	for(int i=0; i<32; i++ ){
		if(NumBin[i]=='1'){
			int y= pow(2, j);
			suma= suma +  y;    //       pow(base, exponente)
		}
		j--;
	}
	return(suma);
}


/////////////////// TipoR ///////////////////
static void add(int rs, int rt, int rd){ 
	BancoRegistros[rd]= BancoRegistros[rs] + BancoRegistros [rt];
	pc++;
	
}

static void addu(int rs, int rt, int rd){ 
	unsigned int regs=BancoRegistros[rs];
	unsigned int regt=BancoRegistros[rt];
	unsigned int regd;
	regd=regs+regt;
	BancoRegistros[rd]= regd;
	pc++;
}

static void and(int rs, int rt, int rd){ 
	
	BancoRegistros[rd]= BancoRegistros[rs] & BancoRegistros[rt];
	pc++;
}

static void jr(int rs){
	 for (int i=0; i<(cont-1); i++){
		 if(inst[i].PCValue==BancoRegistros[rs]){
			 pc=i;
		 }
		 
	 }
}

static void nor(int rs, int rt, int rd){
	int temp;
	temp = BancoRegistros[rs] | BancoRegistros [rt]; 
	BancoRegistros[rd] = ~temp;
	pc++;
}

static void or(int rs, int rt, int rd){
	
	BancoRegistros[rd] = BancoRegistros[rs] | BancoRegistros [rt]; 
	pc++;
}

static void slt(int rs, int rt, int rd){
	
	BancoRegistros[rd] = (BancoRegistros[rs]<BancoRegistros[rt]) ? 1 : 0;
	pc++;
}

static void sltu(int rs, int rt, int rd){    
	unsigned int regs=BancoRegistros[rs];
	unsigned int regt= BancoRegistros[rt];
	BancoRegistros[rd] = (regs<regt) ? 1 : 0;
	pc++;
}

static void sll( int rt, int rd, int shamt){ //listo
	BancoRegistros[rd] = BancoRegistros[rt]  << shamt;
	pc++;
}

static void srl( int rt, int rd, int shamt){ //listo
	BancoRegistros[rd] = BancoRegistros[rt]  >> shamt;
	pc++;
}

static void sub(int rs, int rt, int rd){       
	BancoRegistros[rd]= BancoRegistros[rs] - BancoRegistros[rt]; 
	pc++;
}

static void subu(int rs, int rt, int rd){     
	unsigned int regs=BancoRegistros[rs];
	unsigned int regt= BancoRegistros[rt];
	BancoRegistros[rd]= regs - regt; 
	pc++;
}

//////////////////////////////////////////////////
/////////////////// Tipo I /////////////////////
static void addi(int rs, int rt, int immediate){ //listo
	BancoRegistros[rt] = BancoRegistros[rs] + immediate; 
	pc++;
}

static void andi (int rs, int rt, int immediate){  //listo
	BancoRegistros[rt] = BancoRegistros[rs] & immediate; 
	pc++;
}

static void beq(int rs, int rt, int immediate){   //listo
	if(BancoRegistros[rs]==BancoRegistros[rt]){
		pc=pc+1+immediate;
	}
	else 
		pc++;
}

static void bne(int rs, int rt, int immediate){   //listo
	if(BancoRegistros[rs] !=BancoRegistros[rt]){
		pc=pc+1+immediate;
	}
	else 
		pc++;
}

static void lui(int rt, int immediate){
	BancoRegistros[rt] = immediate<<16;  // para generar los 16 bits menos significativos
	pc++;
}

static void ori(int rs, int rt, int immediate){
	BancoRegistros[rt]= BancoRegistros[rs] | immediate;
	pc++;
}

static void slti_sltiu(int rs, int rt, int immediate){
	BancoRegistros[rt]= (BancoRegistros[rs]<immediate) ? 1:0;
	pc++;
}
//////////////////////////////////////////////////
/////////////////// Tipo j /////////////////////
static void jump(int immediate){       //listo
	for(int i=0; i<(cont-1); i++){
		if(inst[i].PCValue==immediate){
			pc= i ;
		}
	}
}

static void lw(int rs, int rt, int immediate){
	
	addres= immediate+BancoRegistros[rs];         //la direccion de donde sacar
	
	BancoRegistros[rt]=Stack[addres];
	pc++;
}

static void sw(int rs, int rt, int immediate){

	addres= immediate+BancoRegistros[rs];
	Stack[addres]=BancoRegistros[rt];
	pc++;
}

static void jal(int immediate){
	BancoRegistros[31]=inst[pc+1].PCValue;
	for(int i=0; i<(cont-1); i++){
		if(inst[i].PCValue==immediate){
			pc= i ;
		}
	}
}

/////////////////////////////////////////////////

static void obtenerOpcode( char x[]){
	for ( int i =0; i<6; i++){
		opcode[i]=x[i];
	}
}

static void obtenerFunction(char x[]){
	int j=0;		
	for (int i=26; i<32; i++){
		function[j]=x[i];
		j++;
	}
}

static void obtenerRegistroR(char x[]){
	char Rs[5];
	char Rd[5];
	char Rt[5];
	int j1=0;
	int h1=0;
	int g1=0;
	for ( int i =6; i<11; i++){
		Rs[j1]=x[i];
		j1++;
	}
	
	for ( int j =11; j<16; j++){
		Rt[h1]=x[j];
		h1++;
	}
	
	for ( int h =16; h<21; h++){
		Rd[g1]=x[h];
		g1++;
	}
	
	rs=decoBinDecimal(Rs);
	rt=decoBinDecimal(Rt);
	rd=decoBinDecimal(Rd);
}

static void obtenerRegistroI(char x[]){
	char Rs[5];
	char Rt[5];
	int j1=0;
	int h1=0;
	for ( int i =6; i<11; i++){
		Rs[j1]=x[i];
		j1++;
	}
	
	for ( int j =11; j<16; j++){
		Rt[h1]=x[j];
		h1++;
	}
	
	rs=decoBinDecimal(Rs);
	rt=decoBinDecimal(Rt);
	
}

static void obtenerShamt(char x[]){
	char tempShamt[5];
	int j=0;
	for ( int i =21; i<26; i++){
		tempShamt[j]=x[i];
		j++;
	}
	
	shamt=decoBinDecimal(tempShamt);
	
}

static void obtenerImmediate(char x[]){ //decodifica el inmediato con signo del lenguaje maquina
	int j=0;
	char imm[16];
	for (int i=16; i<32; i++){
		imm[j]=x[i];
		j++;		
	}
	immediate= decoBinDecimal2Signo(imm);
}

static void obtenerImmediateUnsigned(char x[]){ //decodifica el inmediato sin signo del lenguaje maquina
	int j=0;
	char imm[16];
	for (int i=16; i<32; i++){
		imm[j]=x[i];
		j++;		
	}
	immediate= decoBinDecimal2Unsigned(imm);
}

static void immediate_J(char x[]){
	int j=0;
	char imm[32];
	char temp[26];
	for (int i=6; i<32; i++){
		temp[j]=x[i];
		j++;		
	}
	int j2=0;
	for (int j1=0; j1<32; j1++){
		if (j1<4){
			imm[j1]='0';
		}
		else if (3<j1<30 ){
			imm[j1]=temp[j2];
			j2++;
		}
		else 
			imm[j1]='0';
	}
	
	immediate= decoBinDeci_32bt(imm);
}

static void DELAY(int milis){
	int delay;
	delay=milis*1000;	
	usleep(delay); 
	
}

int main () {

	Guardarfichero();       
	PC();
	/*BancoRegistros[4]=10000; //Valor en milisegundos
	BancoRegistros[2]=32;*/
	
	/*BancoRegistros[2]=42;
	BancoRegistros[5]=4;*/
	BancoRegistros[19]=4; //Para pruebas 
	BancoRegistros[15]=4; //Para pruebas
	BancoRegistros[29]=469753855; //Para inicializar el stackPointer.
	BancoRegistros[28]=0; //Para inicializar globalPointer
	while ( pc<(cont-1)){
		char x[32];
		strcpy( x , inst[pc].instruccion); //copia la instruccion en variable x para utilizarla en la decodificacion de la instruccion.
		
		if(strcmp(x, "00000000000000000000000000001100")==0){ //// llamado a sistema (SYSCALL)
			if(BancoRegistros[2]==32){ //// pausa del codigo por un tiempo determinado
				printf("Detecte syscall\n");
				if(BancoRegistros[2]==32){ //// pausa del codigo por un tiempo determinado
					printf("Dura 10seg\n");
					DELAY(BancoRegistros[4]);
					printf("Duro 10seg?\n\n");
					pc++;
				}		
			}
			
			else if (BancoRegistros[2]==42){ //// Genera un numero aleatorio con limite de $a1 y lo guarda en $a0
				srand(time(NULL));
				BancoRegistros[4]=rand()%(BancoRegistros[5]+1);
				pc++;
			}
		}
		
		else {
			obtenerOpcode(x);
			//////////////////Tipo R ////////////////////////
			if (strcmp(opcode, "000000") ==0){             
				obtenerFunction(x);  	            // Para saber a cual instruccion tipo R corresponde.
				if (strcmp(function, "100000") == 0){        //Instruccion add
					obtenerRegistroR(x);
					printf("0x%x   instruccion: add $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					add(rs, rt, rd);
				}
				
				else if (strcmp(function, "100001") ==0){   //instruccion addu   //REVISAR UNSIGNED
					obtenerRegistroR(x);
					printf("0x%x   instruccion: addu $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					addu(rs, rt, rd);	
				}
				
				else if (strcmp(function, "100100") ==0){   //instruccion and
					obtenerRegistroR(x);
					printf("0x%x   instruccion: and $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					and(rs, rt, rd);				
				}
				
				else if (strcmp(function, "001000") ==0){   //instruccion jr   
					obtenerRegistroR(x);
					printf("0x%x   instruccion: jr $%i \n\n", inst[pc].PCValue, rs);
					jr(rs);
				}
				
				else if (strcmp(function, "100111") ==0){   //instruccion nor
					obtenerRegistroR(x);
					printf("0x%x   instruccion: nor $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					nor(rs, rt, rd);
				}
				
				else if (strcmp(function, "100101") ==0){   //instruccion or
					obtenerRegistroR(x);
					printf("0x%x   instruccion: or  $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					or(rs, rt, rd);
				}
				
				else if (strcmp(function, "101010") ==0){   //instruccion slt
					obtenerRegistroR(x);
					printf("0x%x   instruccion: slt  $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					slt(rs, rt, rd);
				}
				
				else if (strcmp(function, "101011") ==0){   //instruccion sltu
					obtenerRegistroR(x);
					printf("0x%x   instruccion: sltu  $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					sltu(rs, rt, rd);
				}
				
				else if (strcmp(function, "000000") ==0){   //instruccion sll
					obtenerRegistroR(x);
					obtenerShamt(x);
					printf("0x%x   instruccion: sll $%i, $%i, %i \n\n", inst[pc].PCValue, rd, rt, shamt);
					sll(rt, rd, shamt);
				}
				
				else if (strcmp(function, "000010") ==0){   //instruccion srl
					obtenerRegistroR(x);
					obtenerShamt(x);
					printf("0x%x   instruccion: srl $%i, $%i, %i \n\n", inst[pc].PCValue, rd, rt, shamt);
					srl(rt, rd, shamt);
					
				}
				
				else if (strcmp(function, "100010") ==0){   //instruccion sub
					obtenerRegistroR(x);
					printf("0x%x   instruccion: sub $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					sub(rs, rt, rd);
				}
				
				else if (strcmp(function, "100011") ==0){   //instruccion subu
					obtenerRegistroR(x);
					printf("0x%x   instruccion: subu, $%i, $%i, $%i \n\n", inst[pc].PCValue, rd, rs, rt);
					subu(rs, rt, rd);
				}
				
			}
			
			//////////////////Tipo I ////////////////////////
			else if (strcmp(opcode, "001000") ==0){  // Instruccion addi
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x   instruccion: addi $%i, $%i, %i \n\n", inst[pc].PCValue, rt, rs, immediate);
				addi(rs, rt, immediate);
				
			}
			
			else if (strcmp(opcode, "001001") ==0){  // Instruccion addiu  
				obtenerRegistroI(x);
				obtenerImmediateUnsigned(x);
				printf("0x%x   instruccion: addiu $%i, $%i, %i \n\n", inst[pc].PCValue, rt, rs, immediate);
				addi(rs, rt, immediate);
			}
			
			else if (strcmp(opcode, "001100") ==0){  //Instruccion andi
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x   instruccion: andi $%i, $%i, %i \n\n", inst[pc].PCValue, rt, rs, immediate);
				andi(rs, rt, immediate);
		
			}
			else if (strcmp(opcode, "000100") ==0){ //instruccion beq
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x   instruccion: beq $%i, $%i, %i \n\n", inst[pc].PCValue, rs, rt, immediate);	
				beq (rs,rt, immediate);
				
			}
			
			else if (strcmp(opcode, "000101") ==0){ //instruccion bne
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x   instruccion: bne $%i, $%i, %i \n\n", inst[pc].PCValue, rs, rt, immediate);
				bne(rs, rt, immediate);
			}
			else if (strcmp(opcode, "001111") ==0){ //instruccion lui
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x   instruccion: lui $%i, %i \n\n", inst[pc].PCValue, rt, immediate);
				lui( rt, immediate);
			}
			else if (strcmp(opcode, "001101") ==0){ //instruccion ori
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x   instruccion: ori $%i, $%i, %i \n\n", inst[pc].PCValue, rt, rs, immediate);
				ori(rs, rt, immediate);
			}
			
			else if (strcmp(opcode, "001010") ==0){ //instruccion slti
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x   instruccion: slti $%i, $%i, %i \n\n", inst[pc].PCValue, rt, rs, immediate);
				slti_sltiu(rs, rt, immediate);
			}
			
			else if (strcmp(opcode, "001011") ==0){ //instruccion sltiu
				obtenerRegistroI(x);
				obtenerImmediateUnsigned(x);
				printf("0x%x   instruccion: sltiu $%i, $%i, %i \n\n", inst[pc].PCValue, rt, rs, immediate);
				slti_sltiu(rs, rt, immediate);
			}

			else if (strcmp(opcode, "100011") ==0){ //instruccion lw
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x  intruccion: lw $%i, $%i, %i, \n\n", inst[pc].PCValue, rt, rs, immediate);
				lw(rs, rt, immediate);
				
				
			}
			else if (strcmp(opcode, "101011") ==0){ //instruccion sw
				obtenerRegistroI(x);
				obtenerImmediate(x);
				printf("0x%x  intruccion: sw $%i, $%i, %i, \n\n", inst[pc].PCValue, rt, rs, immediate);
				sw(rs, rt, immediate);
			}
			
			//////////////////Tipo J ////////////////////////
			else if (strcmp(opcode, "000010") ==0){ // instruccion j
				immediate_J(x);
				printf("0x%x   instruccion: j %x \n\n", inst[pc].PCValue, immediate);
				jump(immediate);
			}
			
			else if (strcmp(opcode, "000011") ==0){ // instruccion jal    //PROBAR FUNCIONAMIENTO
				immediate_J(x);
				printf("0x%x   instruccion: jal %x \n\n", inst[pc].PCValue, immediate);
				jal(immediate);
			}
		}
		
	}
	
	printf("resultado: %i\n", BancoRegistros[2]);
	return 0;
}












