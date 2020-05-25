/*Program ini dibuat oleh:

	 Teknik Informatika
	Universitas Udayana
	
Nama		: I Putu Sedana Wijaya
NIM			: 1808561034
E-mail		: sedanawjy@gmail.com
Linkedin	: https://www.linkedin.com/in/i-putu-sedana-wijaya-0109a7188

*/
#include<stdio.h>
#include<stdlib.h>
struct jadwal{
	char kode[8];
	char nama[50];
	int sks;
};

int main(){
	int pilihan=0, n=0, i, j, m, acak, pilih[20], parent[20], iterasi;
	srand((unsigned)time(NULL));
	m=6;
	float chromosome[m][4], baru[m][4], offspring[m][4], f[m], fitness[m], p[m], c[m], r[m], gen, totalf,rata1,rata2;
	struct jadwal kuliah[50];
	
	int totalsks=0;
	while(pilihan!=4){
		system("cls");
		printf("            Program Penjadwalan Kuliah\n            dengan Algoritma Genetika\n");
		printf(" 1. Tambahkan mata kuliah\n 2. Lihat Mata Kuliah\n 3. Lihat Jadwal Kuliah\n 4. Keluar\n  Pilihan: ");
		scanf("%d", &pilihan);
		if(pilihan==1){
			printf("Kode mata kuliah\t: ");
			scanf("%s",&kuliah[n].kode);
			printf("Nama mata kuliah\t: ");
			scanf("%s",&kuliah[n].nama);
			printf("Jumlah SKS\t\t: ");
			scanf("%d",&kuliah[n].sks);
			totalsks = totalsks + (kuliah[n].sks * 50);
			printf("Mata Kuliah sudah diinput!\n");			
			n++;
		}else if(pilihan==2){
			if(n==0){
				printf("Data Kosong!\n");
			}else{
				printf("Kode\tNama Mata Kuliah\tSKS\n");
				for(i=0;i<n;i++){
					printf("%s\t%s\t\t%d\n",kuliah[i].kode,kuliah[i].nama,kuliah[i].sks);
				}
				printf("Total sks = %d x 50 menit = %d menit\n", totalsks/50, totalsks);
			}
		}else if(pilihan==3){
			if(n==0){
				printf("Data Kosong!\n");
			}else{
		iterasi=0;
	//1. Pembentukan Chromosome
				for(i=0;i<m;i++){
					for(j=0;j<4;j++){
						x:
						acak=rand()%totalsks;
						gen=acak;
						if(acak%50!=0){
							goto x;
						}else{
							chromosome[i][j]=gen;
						}
					}
				}
	//2. Evaluasi Chromosome
				for(i=0;i<m;i++){
					f[i]=0;
				}
				totalf=0;
				for(i=0;i<m;i++){
					for(j=0;j<4;j++){
						f[i] = f[i] + chromosome[i][j];
					}
					f[i] = f[i] - totalsks;
					totalf = totalf + f[i];
				}
				rata1=totalf/m;
	//3. Seleksi Chromosome
				float totalfit, bantu;
				awal:
				totalfit=0;
				for(i=0;i<m;i++){
					fitness[i]=1/(f[i]+1);
					totalfit = totalfit + fitness[i];
				}
				bantu=0;
				for(i=0;i<m;i++){
					p[i] = fitness[i]/totalfit;
					bantu= bantu + p[i];
					c[i] = bantu;
				}
				for(i=0;i<m;i++){
					r[i] = rand() / (float) RAND_MAX;
					for(j=0;j<m;j++){
						if(r[i] < c[j]){
							pilih[i] = j;
							break;
						}
					}
				}
				for(i=0;i<m;i++){
					for(j=0;j<4;j++){
						baru[i][j] = chromosome[pilih[i]][j];
					}
				}
	//4. Crossover Chromosome
				int k, induk;		
				in:
				induk=-1;
				for(i=0;i<m;i++){
					r[i] = rand() / (float) RAND_MAX;
					if(r[i] < 0.5){ //crossover probability = 25%
						induk++;
						parent[induk] = i;
					}
				}
				if(induk<=0){
					goto in;
				}
				induk++;
				parent[induk]=parent[0];
				for(i=0;i<induk;i++){
					acak = rand() % 4; //panjang chromosome = 4;
					c[i] = acak;
				}
				for(i=0;i<m;i++){
					for(j=0;j<4;j++){
						offspring[i][j]=baru[i][j];
					}
				}
				for(k=0;k<induk;k++){
					for(j=0;j<4;j++){
						if(j != c[k] && k != parent[k]){
							offspring[parent[k]][j] = baru[parent[k+1]][j];
						}
					}
				}
	//5. Mutasi Chromosome
				int jmlmutasi, nilai, posisi[20], fungsi;
				jmlmutasi = 0.1*4*m;
				nilai = 0;
				for(i=0;i<jmlmutasi;i++){
					posisi[i] = rand()%24;
				}
				k=0;
				for(i=0;i<m;i++){
					for(j=0;j<4;j++){
						if( nilai == posisi[k] ){
							z:
							acak = rand()%totalsks;
							if(acak%50!=0){
								goto z;
							}
							offspring[i][j] = acak;
							k++;
						}
						nilai++;
					}
				}
				totalf=0;
				for(i=0;i<m;i++){
					fungsi=0;
					for(j=0;j<4;j++){
						fungsi = fungsi + offspring[i][j];
					}
					fungsi = fungsi - totalsks;
					f[i] = fungsi;
					totalf = totalf + f[i];
				}
				rata2=totalf/m;
				iterasi++;
	//6. Kondisi Terminasi
				int cek=0, cek2=0, total, tanda=0, hasil;
				float jadwal[m][4];
				if(rata2>rata1){
					goto awal;
				}else{
					for(i=0;i<m;i++){
						total=0;
						for(j=0;j<4;j++){
							total = total + offspring[i][j];
						}
						if(total >= totalsks){
							cek=0;
							for(k=0;k<4;k++){
								if(offspring[i][k] > 450){
									break;
								}else{
									cek++;
								}
							}
							if(cek==4){
								hasil = i;
								tanda=1;
								break;
							}
						}else{
							cek2++;
						}
					}
					if(cek2==4){
						goto awal;
					}else if(cek2!=4){
						if(tanda==1){
							printf("\n=========================================================================\n");
							printf("\tGen Terbaik setelah %d iterasi: { ",iterasi);
							for(i=0;i<m;i++){
								if(i == hasil){
									for(j=0;j<4;j++){
										printf("%.0f ", offspring[hasil][j]);
										jadwal[hasil][j]=offspring[hasil][j];
									}
									break;
								}
							}
							printf("}\n");
							printf("=========================================================================\n");
						}else{
							goto awal;
						}
					}
				}
	//7. OUTPUT
	int save[50], jam, menit, s;
				char output[100][100];
				for(k=0;k<n;k++){
					save[k] = kuliah[k].sks * 50.0;
				}
				printf("\n");
				i=hasil;
				printf("\t\tKode\tMata Kuliah\tSKS\n");
				for(j=0;j<4;j++){
					jam=8;
					menit=30;
					if(j==0){
						printf("Senin:\n");
					}else if(j==1){
						printf("Selasa:\n");
					}else if(j==2){
						printf("Rabu:\n");
					}else if(j==3){       
						printf("Kamis:\n");
					}
					for(k=0;k<n;k++){
						tanda=0;
						if(save[k] <= jadwal[hasil][j] && save[k]!=0){
							printf("\t%s\t%s\t\t%d\tpukul %d:%d - ",kuliah[k].kode,kuliah[k].nama,kuliah[k].sks,jam,menit);
							menit = menit + save[k];
							if(menit >= 60){
								s = menit / 60;
								jam = jam + s;
								s = menit % 60;
								menit = s;
							}
							printf("%d:%d \n", jam, menit);
							jadwal[hasil][j] = jadwal[hasil][j] - save[k];
							save[k]=0;
						}
					}
				}
				printf("\n");
			}
		}
		system("pause");
	}
	return 0;
}
