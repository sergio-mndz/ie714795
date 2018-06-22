#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int dia, mes, anio;
}Fecha;

typedef struct{
	int id;
	char nombre[20];
	char apePaterno[20];
	char apeMaterno[20];
	Fecha nacimiento;
}Cliente;

typedef struct{
	int idCuenta;
	int idUsuario;
	int saldo;
	Fecha apertura;
}Cuenta;

typedef struct{
	int idTransaccion;
	int tipo;
	int idInicio;
	int idFinal;
	Fecha fecha;
	int monto;
}Transaccion;

Fecha capturarFecha();

int menuClientes(char *path);
int menuCuentas(char *path);
int menuTransacciones(char* path, char* cuentas);

int direccionArchivos(char** clientes,char** cuentas,char** transacciones);

Cliente nuevoCliente(int id);
void imprimirCliente(FILE* archivo);
void imprimirClientes(FILE* archivo);
FILE* buscarCliente(FILE* archivo, int id);
int borrarCliente(FILE* archivo,char* path);

Cuenta nuevaCuenta(int id);
void imprimirCuenta(FILE* archivo);
void imprimirCuentas(FILE* archivo);
FILE* buscarCuenta(FILE* archivo, int id);
int borrarCuenta(FILE* archivo,char* path);


Transaccion tipoTransaccion(int id, FILE* cuentas);


int main(){
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	char *clientes, *cuentas, *transacciones;
	int opcion;
	direccionArchivos(&clientes,&cuentas,&transacciones);

	//MENU PRINCIPAL
	do{
	printf("\n<<Sistema MyDB>>\n");
	printf("1) Clientes\n");
	printf("2) Cuentas\n");
	printf("3) Transacciones\n");
	printf("4) Salir\n");
	printf("Opcion: ");
	scanf("%d", &opcion);
	switch(opcion){
		case 1:
			menuClientes(clientes);
			break;
		case 2:
			menuCuentas(cuentas);
			break;
		case 3:
			menuTransacciones(transacciones,cuentas);
			break;
	}
	}while(opcion!=4);
	return 0;
}

Fecha capturarFecha(){
	Fecha new;
	printf("(dd/mm/aaaa): ");
	scanf("%d/%d/%d", &new.dia, &new.mes, &new.anio);
	return new;
}

int direccionArchivos(char** clientes,char** cuentas,char** transacciones){
	FILE*  first;
	char *path;
	int tam;
	first=fopen("mydb.sys", "a+");
	if(first==NULL)
		return -1;
	if (ftell(first)==0){
		char c;
		printf("Primera vez inciando mySB\nIndique la direccion de los nuevos archivos: ");
		while((c=getchar())!='\n')
			fputc(c,first);
	}
	fseek(first,0,SEEK_END);
	tam=ftell(first);
	path=(char*)malloc(tam);
	*clientes=(char*)malloc((tam+16));
	*cuentas=(char*)malloc((tam+15));
	*transacciones=(char*)malloc((tam+20));
	fseek(first, 0, SEEK_SET);
	fscanf(first,"%[^EOF]",path);
	strcpy(*clientes,path);
	strcpy(*cuentas,path);
	strcpy(*transacciones,path);
	strcat(*clientes,"clientes.dat");
	strcat(*cuentas,"cuentas.dat");
	strcat(*transacciones,"transaccioness.dat");
	free(path);
	fclose(first);
	return 0;
}

int menuClientes(char *path){
	FILE* clientes;
	int opcion1,id;
	printf("\n1) Nuevo Cliente\n");
	printf("2) Bucar Cliente\n");
	printf("3) Eliminar Cliente\n");
	printf("4) Imprimir Cliente\n");
	printf("Opcion: ");
	scanf("%d",&opcion1);
	switch(opcion1){
		case 1:
			clientes=fopen(path,"rb+");
			if(clientes==NULL){
				clientes=fopen(path,"wb");
				if(clientes==NULL)
					return -1;
				id=1;
			}
			else{
				fread(&id,sizeof(int),1, clientes);
				fseek(clientes, 0, SEEK_SET);
				id++;
			}
			fwrite(&id,sizeof(int),1,clientes);
			Cliente new=nuevoCliente(id);
			fseek(clientes,0,SEEK_END);
			fwrite(&new,sizeof(Cliente),1,clientes);
			break;
		case 2:
			clientes=fopen(path,"rb");
			if(clientes==NULL)
				return -1;
			printf("Id de usuario: ");scanf("%d",&id);
			printf("%-13s%-23s%-23s%-23sFecha de nacimiento\n","ID Usuario","Nombre", "Apellido paterno","Apellido materno");
			imprimirCliente(buscarCliente(clientes, id));
			break;
		case 3:
			clientes=fopen(path,"rb");
			if(clientes==NULL)
				return -1;
			printf("Id de usuario: ");scanf("%d",&id);
			if(buscarCliente(clientes, id) != NULL){
				borrarCliente(clientes,path);
			}
			break;
		case 4:
			clientes=fopen(path,"rb");
			if(clientes==NULL)
				return -1;
			imprimirClientes(clientes);
			break;
	}
	fclose(clientes);
	return 0;
}

Cliente nuevoCliente(int id){
	Cliente new;
	new.id=id;
	printf("Nombre: ");scanf("%s", new.nombre);
	printf("Apellido Paterno: ");scanf("%s", new.apePaterno);
	printf("Apellido Materno: ");scanf("%s", new.apeMaterno);
	printf("Fecha de nacimiento ");
	new.nacimiento=capturarFecha();
	return new;
}

void imprimirCliente(FILE* archivo){
	if(archivo!=NULL){
		Cliente cliente;
		fread(&cliente, sizeof(Cliente), 1,archivo);
		printf("%-13d%-23s%-23s%-23s%02d/%02d/%04d\n",
				cliente.id,
				cliente.nombre,
				cliente.apePaterno,
				cliente.apeMaterno,
				cliente.nacimiento.dia,
				cliente.nacimiento.mes,
				cliente.nacimiento.anio);
	}
}

void imprimirClientes(FILE* archivo){
	char c;
	fseek(archivo,sizeof(int),SEEK_SET);
	printf("%-13s%-23s%-23s%-23sFecha de nacimiento\n","ID Usuario","Nombre", "Apellido paterno","Apellido materno");
	printf("-------------------------------------------------------------------------------------------------------\n");
	while((c=fgetc(archivo))!=EOF){
		fseek(archivo,-sizeof(char),SEEK_CUR);
		imprimirCliente(archivo);
	}
}

FILE* buscarCliente(FILE* archivo, int id){
	int temp;
	char c;
	fseek(archivo,sizeof(int),SEEK_SET);
	while((c=fgetc(archivo))!=EOF){
		fseek(archivo,-1,SEEK_CUR);
		fread(&temp,sizeof(int),1,archivo);
		if(temp==id){
			fseek(archivo,-(sizeof(int)),SEEK_CUR);
			return archivo;
		}
		fseek(archivo,sizeof(Cliente)-sizeof(int),SEEK_CUR);
	}
	printf("Cliente no encontrado\n");
	return NULL;
}

int borrarCliente(FILE *archivo, char * path){
	int posicion, numClientes;
	Cliente *clientes;
	posicion=(ftell(archivo))/sizeof(Cliente);
	fseek(archivo,0,SEEK_END);
	numClientes=(ftell(archivo)/sizeof(Cliente));
	fseek(archivo,0,SEEK_SET);
	clientes=(Cliente*)malloc(numClientes*sizeof(Cliente));
	fseek(archivo,0,SEEK_SET);
	fread(clientes,sizeof(Cliente),numClientes,archivo);
	for(int i=posicion;i<numClientes-1;i++)
		clientes[i]=clientes[i+1];
	fclose(archivo);

	archivo=fopen(path,"wb");
	if(archivo==NULL)
		return -1;
	fwrite(clientes,sizeof(Cliente),numClientes-1,archivo);
	free(clientes);
	return 0;
}

int menuCuentas(char *path){
	FILE* cuentas;
	int opcion2,id;
	printf("\n1) Nueva cuenta\n");
	printf("2) Buscar cuenta\n");
	printf("3) Eliminar cuenta\n");
	printf("4) Imprimir cuenta\n");
	printf("Opcion: ");
	scanf("%d",&opcion2);
	switch(opcion2){
		case 1:
			cuentas=fopen(path,"rb+");
			if(cuentas==NULL){
				cuentas=fopen(path,"wb");
				if(cuentas==NULL)
					return -1;
				id=1;
			}
			else{
				fread(&id,sizeof(int),1,cuentas);
				fseek(cuentas,0,SEEK_SET);
				id++;
			}
			fwrite(&id,sizeof(int),1,cuentas);
			Cuenta new=nuevaCuenta(id);
			fseek(cuentas,0,SEEK_END);
			fwrite(&new,sizeof(Cuenta),1,cuentas);
			break;
		case 2:
			cuentas=fopen(path,"rb");
			if(cuentas==NULL)
				return -1;
			printf("Id de cuenta: ");scanf("%d",&id);
			printf("\n%-12s%-13s%-13sFecha de apertura\n","ID Cuenta","ID Usuario","Saldo");
			imprimirCuenta(buscarCuenta(cuentas, id));
			break;
		case 3:
			cuentas=fopen(path,"rb");
			if(cuentas==NULL)
				return -1;
			printf("Id de cuenta: ");scanf("%d",&id);
			if(buscarCuenta(cuentas,id)!=NULL)
				borrarCuenta(cuentas,path);
			break;
		case 4:
			cuentas=fopen(path,"rb");
			if(cuentas==NULL)
				return -1;
			imprimirCuentas(cuentas);
			break;
	}
	fclose(cuentas);
	return 0;
}

Cuenta nuevaCuenta(int id){
	Cuenta new;
	new.idCuenta=id;
	printf("Id del cliente: ");scanf("%d", &new.idUsuario);
	printf("Saldo de apertura: ");scanf("%d", &new.saldo);
	printf("Fecha de apertura");
	new.apertura=capturarFecha();
	return new;
}

void imprimirCuenta(FILE* archivo){
	if(archivo!=NULL){
		Cuenta cuenta;
		fread(&cuenta, sizeof(Cuenta), 1,archivo);
		printf("%-12d%-13d%-13d%02d/%02d/%04d\n",
				cuenta.idCuenta,
				cuenta.idUsuario,
				cuenta.saldo,
				cuenta.apertura.dia,
				cuenta.apertura.mes,
				cuenta.apertura.anio);
	}
}
void imprimirCuentas(FILE* archivo){
	char c;
	fseek(archivo,sizeof(int),SEEK_SET);
	printf("\n%-12s%-13s%-13sFecha de apertura\n","ID Cuenta","ID Usuario","Saldo");
	printf("--------------------------------------------------------------\n");
	while((c=fgetc(archivo))!=EOF){
		fseek(archivo,-sizeof(char),SEEK_CUR);
		imprimirCuenta(archivo);
	}
}

FILE* buscarCuenta(FILE* archivo, int id){
	int temp;
	char c;
	fseek(archivo,sizeof(int),SEEK_SET);
	while((c=fgetc(archivo))!=EOF){
		fseek(archivo,-1,SEEK_CUR);
		fread(&temp,sizeof(int),1,archivo);
		if(temp==id){
			fseek(archivo,-(sizeof(int)),SEEK_CUR);
			return archivo;
		}
		fseek(archivo,sizeof(Cuenta)-sizeof(int),SEEK_CUR);
	}
	printf("Cuenta no encontrado\n");
	return NULL;
}

int borrarCuenta(FILE *archivo, char * path){
	int posicion, numClientes;
	Cuenta *cuentas;
	posicion=(ftell(archivo))/sizeof(Cuenta);
	fseek(archivo,0,SEEK_END);
	numClientes=(ftell(archivo)/sizeof(Cuenta));
	fseek(archivo,0,SEEK_SET);
	cuentas=(Cuenta*)malloc(numClientes*sizeof(Cuenta));
	fseek(archivo,0,SEEK_SET);
	fread(cuentas,sizeof(Cuenta),numClientes,archivo);
	for(int i=posicion;i<numClientes-1;i++)
		cuentas[i]=cuentas[i+1];
	fclose(archivo);

	archivo=fopen(path,"wb");
	if(archivo==NULL)
		return -1;
	fwrite(cuentas,sizeof(Cuenta),numClientes-1,archivo);
	free(cuentas);
	return 0;
}


int menuTransacciones(char* path, char* pathCuentas){
	FILE *transacciones,*cuentas;
	int id;

	transacciones=fopen(path,"rb+");
	if(transacciones==NULL){
		transacciones=fopen(path,"wb");
		if(transacciones==NULL)
			return -1;
		id=1;
	} else {
		fread(&id,sizeof(int),1,transacciones);
		fseek(transacciones, 0, SEEK_SET);
		id++;
	}

	cuentas=fopen(pathCuentas,"rb+");
	if(cuentas==NULL)
		return -1;

	Transaccion new;
	new=tipoTransaccion(id,cuentas);
	fseek(transacciones,0,SEEK_END);
	fwrite(&new,sizeof(Transaccion),1,transacciones);
	fclose(cuentas);
	fclose(transacciones);
	return 0;
	fclose(cuentas);
	fclose(transacciones);
}

Transaccion tipoTransaccion(int id, FILE* cuentas){
	Transaccion temp;
	int saldoManda, saldoRecibe;
	temp.idTransaccion=0;
	printf("Tipo de transaccion:\n");
	printf("1) Retiro\n");
	printf("2) Deposito\n");
	printf("3) Transferencia\n");
	scanf("%d",&temp.tipo);
	switch(temp.tipo){
	case 1:
		printf("ID de cuenta origen: ");
		scanf("%d", &temp.idInicio);
		if(buscarCuenta(cuentas, temp.idInicio)==NULL){
			printf("Cuenta inexistente\n");
			return temp;
		}
		fseek(cuentas,2*sizeof(int),SEEK_CUR);
		fread(&saldoManda,sizeof(int), 1, cuentas);
		temp.idFinal=0;
		printf("Monto: ");
		scanf("%d", &temp.monto);
		if(temp.monto>saldoManda){
			printf("Saldo insufisiente\n");
			return temp;
		}
		saldoManda -= temp.monto;
		printf("Fecha");
		temp.fecha=capturarFecha();
		buscarCuenta(cuentas, temp.idInicio);
		fseek(cuentas, 2*sizeof(int), SEEK_CUR);
		fwrite(&saldoManda, sizeof(int), 1, cuentas);
		break;
	case 2:
		printf("Id cuenta destino: ");
		scanf("%d",&temp.idFinal);
		if(buscarCuenta(cuentas,temp.idFinal)==NULL){
			printf("Cuenta inexistente\n");
			return temp;
		}
		fseek(cuentas,2*sizeof(int),SEEK_CUR);
		fread(&saldoRecibe, sizeof(int), 1, cuentas);
		temp.idInicio=0;
		printf("Monto: ");
		scanf("%d", &temp.monto);
		saldoRecibe += temp.monto;
		printf("Fecha");
		temp.fecha=capturarFecha();
		buscarCuenta(cuentas,temp.idFinal);
		fseek(cuentas,2*sizeof(int),SEEK_CUR);
		fwrite(&saldoRecibe,sizeof(int),1,cuentas);
		break;
	case 3:
		printf("Id cuenta origen: ");
		scanf("%d", &temp.idInicio);
		if(buscarCuenta(cuentas,temp.idInicio)==NULL){
			printf("Cuenta inexistente\n");
			return temp;
		}
		fseek(cuentas, 2*sizeof(int), SEEK_CUR);
		fread(&saldoManda, sizeof(int), 1, cuentas);
		printf("Id cuenta destino: ");
		scanf("%d", &temp.idFinal);
		if(buscarCuenta(cuentas,temp.idFinal)==NULL){
			printf("Cuenta inexistente\n");
			return temp;
		}
		fseek(cuentas, 2*sizeof(int), SEEK_CUR);
		fread(&saldoRecibe, sizeof(int), 1, cuentas);
		printf("Monto: ");
		scanf("%d",&temp.monto);
		if(temp.monto > saldoManda){
			printf("Saldo insufisiente\n");
			return temp;
		}
		saldoManda-=temp.monto;
		saldoRecibe+=temp.monto;
		printf("Fecha");
		temp.fecha=capturarFecha();
		buscarCuenta(cuentas,temp.idFinal);
		fseek(cuentas,2*sizeof(int),SEEK_CUR);
		fwrite(&saldoManda,sizeof(int),1,cuentas);
		buscarCuenta(cuentas,temp.idInicio);
		fseek(cuentas,2*sizeof(int),SEEK_CUR);
		fwrite(&saldoManda,sizeof(int),1,cuentas);
		break;
	}
	temp.idTransaccion=id;
	return temp;
}
