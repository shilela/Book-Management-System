//图书管理系统主界面
#include<stdio.h>
#include<Windows.h>
#include<ctype.h>
#include<string.h>

//**************常数*********************
#define PENALTY 0.1//罚金0.1元一天
#define DEADLINE 60//最长借书时间60天

//***************定义结构体******************
struct Date//日期
{
	int year;
	int month;
	int day;
};

struct Book//书
{
	char issn[30];//issn编号
	char title[30];//书名
	char publisher[20];//出版社
	char author[20];//作者
	double price;//价格
	char available;//是否借走
	char no[10];//被谁借走
	struct Book *next;
};

struct History//借阅历史
{
	char no[10];//学号
	char issn[30];//issn编号
	struct Date borrow_date;//借书时间
	struct Date return_date;//还书时间
	double penalty;//违约金
	struct History *next;
};

struct Stu//学生
{
	char no[10];//学号
	char name[10];//姓名
	char class_no[15];//班级
	char phone_number[15];//联系方式
	char gender;//性别
	struct Stu *next;
};

//******************全局变量***********************
struct Stu *stu_head=NULL;//学生头指针
struct Book *book_head=NULL;//书本头指针
struct History *history_head=NULL;//历史头指针

//************************初始化/清空数据****************************
void initialization(void)
{
	FILE *fp;
	fp=fopen("C:\\Users\\shile\\Documents\\stu.txt","wb");
	fclose(fp);
	fp=fopen("C:\\Users\\shile\\Documents\\book.txt","wb");
	fclose(fp);
	fp=fopen("C:\\Users\\shile\\Documents\\history.txt","wb");
	fclose(fp);
}
//*********************读写*****************************
void read_file(void);//申请内存空间并读文件
void write_file(void);//写文件并释放内存空间

void read_file(void)//读
{
	FILE *fp;
	struct Stu *stu_p1=NULL;
	struct Stu *stu_p2=NULL;
	struct Book *book_p1=NULL;
	struct Book *book_p2=NULL;
	struct History *history_p1=NULL;
	struct History *history_p2=NULL;
	//读学生文件
	if((fp=fopen("C:\\Users\\shile\\Documents\\stu.txt","rb"))==NULL)//打开失败重新创建
		fp=fopen("C:\\Users\\shile\\Documents\\stu.txt","wb+");
	stu_head=stu_p1=stu_p2=(struct Stu *)malloc(sizeof(struct Stu));
	fread(stu_p1,sizeof(struct Stu),1,fp);
	while(!feof(fp))
	{
		stu_p1=stu_p2;
		stu_p2=(struct Stu *)malloc(sizeof(struct Stu));
		stu_p1->next=stu_p2;
		fread(stu_p2,sizeof(struct Stu),1,fp);
	}
	if(stu_p1==stu_p2)//文件为空
		stu_head=NULL;
	else
		stu_p1->next=NULL;
	free(stu_p2);//最后一个是无效的空间
	fclose(fp);
	//读图书文件
	if((fp=fopen("C:\\Users\\shile\\Documents\\book.txt","rb"))==NULL)//打开失败重新创建
		fp=fopen("C:\\Users\\shile\\Documents\\book.txt","wb+");
	book_head=book_p1=book_p2=(struct Book *)malloc(sizeof(struct Book));
	fread(book_p1,sizeof(struct Book),1,fp);;
	while(!feof(fp))
	{
		book_p1=book_p2;
		book_p2=(struct Book *)malloc(sizeof(struct Book));
		book_p1->next=book_p2;
		fread(book_p2,sizeof(struct Book),1,fp);
	}
	if(book_p1==book_p2)//文件为空
		book_head=NULL;
	else
		book_p1->next=NULL;
	free(book_p2);//最后一个是无效的空间
	fclose(fp);
	//读借阅历史文件
	if((fp=fopen("C:\\Users\\shile\\Documents\\history.txt","rb"))==NULL)//打开失败重新创建
		fp=fopen("C:\\Users\\shile\\Documents\\history.txt","wb+");
	history_head=history_p1=history_p2=(struct History *)malloc(sizeof(struct History));
	fread(history_p1,sizeof(struct History),1,fp);
	while(!feof(fp))
	{
		history_p1=history_p2;
		history_p2=(struct History *)malloc(sizeof(struct History));
		history_p1->next=history_p2;
		fread(history_p2,sizeof(struct History),1,fp);
	}
	if(history_p1==history_p2)//文件为空
		history_head=NULL;
	else
		history_p1->next=NULL;
	free(history_p2);//最后一个是无效的空间
	fclose(fp);
}

void write_file(void)//写
{
	FILE *fp;
	struct Stu *stu_p1=NULL;
	struct Stu *stu_p2=NULL;
	struct Book *book_p1=NULL;
	struct Book *book_p2=NULL;
	struct History *history_p1=NULL;
	struct History *history_p2=NULL;
	//写学生文件
	fp=fopen("C:\\Users\\shile\\Documents\\stu.txt","wb");
	if(stu_head!=NULL)//不为空，写数据
	{
		stu_p1=stu_p2=stu_head;
		while(stu_p2!=NULL)
		{
			stu_p1=stu_p2;
			fwrite(stu_p1,sizeof(struct Stu),1,fp);
			stu_p2=stu_p1->next;
		}
	}
	fclose(fp);
	//写图书文件
	fp=fopen("C:\\Users\\shile\\Documents\\book.txt","wb");
	if(book_head!=NULL)//不为空，写数据
	{
		book_p1=book_p2=book_head;
		while(book_p2!=NULL)
		{
			book_p1=book_p2;
			fwrite(book_p1,sizeof(struct Book),1,fp);
			book_p2=book_p1->next;
		}
	}
	fclose(fp);
	//写历史文件
	fp=fopen("C:\\Users\\shile\\Documents\\history.txt","wb");
	if(history_head!=NULL)//不为空，写数据
	{
		history_p1=history_p2=history_head;
		while(history_p2!=NULL)
		{
			history_p1=history_p2;
			fwrite(history_p1,sizeof(struct History),1,fp);
			history_p2=history_p1->next;
		}
	}
	fclose(fp);

}
void freeall(void)//释放空间
{
	struct Stu *stu_p1=NULL;
	struct Stu *stu_p2=NULL;
	struct Book *book_p1=NULL;
	struct Book *book_p2=NULL;
	struct History *history_p1=NULL;
	struct History *history_p2=NULL;
	if(stu_head!=NULL)//不为空
	{
		stu_p1=stu_p2=stu_head;
		while(stu_p2!=NULL)
		{
			stu_p1=stu_p2;
			stu_p2=stu_p1->next;
			free(stu_p1);//释放空间	
		}
		stu_head=NULL;
	}
	if(book_head!=NULL)//不为空
	{
		book_p1=book_p2=book_head;
		while(book_p2!=NULL)
		{
			book_p1=book_p2;
			book_p2=book_p1->next;
			free(book_p1);//释放空间
		}
		book_head=NULL;
	}
	if(history_head!=NULL)//不为空，写数据
	{
		history_p1=history_p2=history_head;
		while(history_p2!=NULL)
		{
			history_p1=history_p2;
			history_p2=history_p1->next;
			free(history_p1);//释放空间
		}
		history_head=NULL;
	}
}

//*****************转换大小写，并消除回车************************
char upper_getchar(void)
{
	char ch;
	while (ch = toupper(getchar()))
	{
		if (ch == '\n')
			continue;
		else
			break;
	}
	return ch;
}
//**********************计算日期间间隔***************************
int datecmp(struct Date start,struct Date end) //判断日期大小是否合法
{
	if(start.year*10000+start.month*100+start.day<=end.year*10000+end.month*100+end.day)//把日期转化为20180227的形式来比大小
		return 1;//正确
	else
		return -1;//错误
}

int cal_date(struct Date start,struct Date end)//计算日期间隔
{
	if(datecmp(start,end)==-1)
	{
		puts("日期错误");
		return -1;
	}
	else
	{
		int y1,m1,d1;
		int y2,m2,d2;
		m1 = (start.month + 9) % 12;
		y1 = start.year - m1/10;
		d1 = 365*y1 + y1/4 - y1/100 + y1/400 + (m1*306 + 5)/10 + (start.day - 1);
		m2 = (end.month + 9) % 12;
		y2 = end.year- m2/10;
		d2 = 365*y2 + y2/4 - y2/100 + y2/400 + (m2*306 + 5)/10 + (end.day - 1);
 
		return (d2 - d1);//日期间隔
	}
}

//****************查询系统**********************
void query(void);//查询系统
int search_book(char issn[],struct Book **book_p1,struct Book **book_p2);//图书查询
int search_stu(char no[],struct Stu **stu_p1,struct Stu **stu_p2);//学生信息查询
int search_history(char no[],char issn[],struct History **history_p1,struct History **history_p2);//历史查询
void return_book_now(void);//催缴图书
void query(void)
{
	struct Stu *stu_p1=NULL;
	struct Book *book_p1=NULL;
	struct History *history_p1=NULL;
	struct Stu *stu_p2=NULL;
	struct Book *book_p2=NULL;
	struct History *history_p2=NULL;
	char buffer_issn[30];//书籍issn编号
	char buffer_no[30];//学生学号
	char option;
	system("cls");
	do
	{
		puts("************查询系统************");
		puts("A.图书查询");
		puts("B.学生信息查询");
		puts("C.历史信息查询");
		puts("D.催缴图书");
		puts("Q.返回图书管理系统");
		puts("请输入选项：按回车键确认，大小写均可");
		switch (option = upper_getchar())
		{
			case 'A':puts("请输入issn编号，按回车确认");
					 scanf("%s",buffer_issn);
					 search_book(buffer_issn,&book_p1,&book_p2); 
					 break;
			case 'B':puts("请输入学号，按回车确认");
					 scanf("%s",buffer_no);
					 search_stu(buffer_no,&stu_p1,&stu_p2);
					 break;
			case 'C':puts("请输入学号，按回车确认");
					 scanf("%s",buffer_no);
					 search_history(buffer_no,"ALL",&history_p1,&history_p2);//"ALL"代表查该学生所有
					 break;
			case 'D':return_book_now();
			case 'Q':break;
			default:puts("\n\n请输入对应操作的英文字母选项！！！");
					system("Pause");
					break;
		}
		system("cls");
	} while (option != 'Q');
}
//查询书
int search_book(char issn[],struct Book **book_p1,struct Book **book_p2)//p1为前一个指针，p2是待查项指针
{
	int flag=0;//标记找没找到，初始值0
	*book_p1=*book_p2=book_head;
	while(*book_p2!=NULL)
	{
		if(strcmp(issn,(*book_p2)->issn)==0)
		{
			flag=1;
			break;
		}
		*book_p1=*book_p2;
		*book_p2=(*book_p1)->next;
	}
	if(flag)//找到了
	{
		puts("找到此书");
		printf("书名：%s issn编号：%s \n出版社：%s 作者：%s \n价格：%lf \n",
				(*book_p2)->title,(*book_p2)->issn,
				(*book_p2)->publisher,(*book_p2)->author,
				(*book_p2)->price);
		printf("被谁借走：%s\n",(*book_p2)->no);
	}
	else
		puts("无此记录！！！");
	system("pause");

	return flag;
}

int search_stu(char no[],struct Stu **stu_p1,struct Stu **stu_p2)//p1为前一个指针，p2是待查项指针
{
	int flag=0;//标记找没找到，初始值0
	*stu_p1=*stu_p2=stu_head;
	while(*stu_p2!=NULL)
	{
		if(strcmp(no,(*stu_p2)->no)==0)
		{
			flag=1;
			break;
		}
		*stu_p1=*stu_p2;
		*stu_p2=(*stu_p1)->next;
	}
	if(flag)//找到了
	{
		puts("找到此学生");
		printf("学号:%s 姓名:%s 班级:%s 联系方式:%s 性别:%c\n",(*stu_p2)->no,(*stu_p2)->name,(*stu_p2)->class_no,
			(*stu_p2)->phone_number,(*stu_p2)->gender);
	}
	else
		puts("无此记录！！！");
	system("pause");
	
	return flag;
}

int search_history(char no[],char issn[],struct History **history_p1,struct History **history_p2)//p1为前一个指针，p2是待查项指针
{
	int flag=0;//标记找没找到，初始值0
	*history_p1=*history_p2=history_head;
	if(strcmp(issn,"ALL")==0)
	{
		while(*history_p2!=NULL)
		{
			if((strcmp(no,(*history_p2)->no)==0))
			{
				flag=1;
				printf("学号:%s issn编号：%s\n借书日期：%d/%d/%d\n还书日期：%d/%d/%d\n违约金：%lf\n",
				(*history_p2)->no,(*history_p2)->issn,
				(*history_p2)->borrow_date.year,(*history_p2)->borrow_date.month,(*history_p2)->borrow_date.day,
				(*history_p2)->return_date.year,(*history_p2)->return_date.month,(*history_p2)->return_date.day,
				(*history_p2)->penalty);
				puts("**********************");
			}
			*history_p1=*history_p2;
			*history_p2=(*history_p1)->next;
		}
		puts("**********************");
		system("pause");
	}
	else
	{
		while(*history_p2!=NULL)
		{
			if(strcmp(no,(*history_p2)->no)==0&&strcmp(issn,(*history_p2)->issn)==0&&(*history_p2)->return_date.year==0)//学号找到，书号找到，且没有还书
			{
				flag=1;
				break;//找到，跳出
			}
			*history_p1=*history_p2;
			*history_p2=(*history_p1)->next;
		}
		if(flag)//找到了
		{
			puts("找到此记录");
			printf("学号:%s issn编号：%s\n借书日期：%d/%d/%d\n还书日期：%d/%d/%d\n违约金：%lf\n",
			(*history_p2)->no,(*history_p2)->issn,
			(*history_p2)->borrow_date.year,(*history_p2)->borrow_date.month,(*history_p2)->borrow_date.day,
			(*history_p2)->return_date.year,(*history_p2)->return_date.month,(*history_p2)->return_date.day,
			(*history_p2)->penalty);
		}
		else
			puts("无此记录！！！");
		system("pause");
	}
	return flag;
}

void return_book_now(void)//该还书了，催缴
{
	struct History *history_p;
	struct Stu *stu_p1=NULL;
	struct Stu *stu_p2=NULL;
	struct Date date;
	puts("请输入今天日期");
	scanf("%d%d%d",&date.year,&date.month,&date.day);
	history_p=history_head;
	while(history_p!=NULL)
	{
		if(history_p->return_date.year==0&&cal_date(history_p->borrow_date,date)>DEADLINE)//没还书且超出日期
		{
			printf("催缴:书本编号：%s 学号:%s\n",history_p->issn,history_p->no);
			search_stu(history_p->no,&stu_p1,&stu_p2);
			puts("****************************************");
		}
		history_p=history_p->next;
	}
	system("pause");
}


//***********************学生管理系统*******************
void stu_management(void);//学生管理系统

void add_stu(void);//添加学生
void modify_stu(void);//修改学生信息
void delete_stu(void);//删除学生信息
void view_stu(void);//查看学生信息


void stu_management(void)
{
	char option;
	system("cls");
	do
	{
		puts("************学生信息管理************");
		puts("A.添加学生信息");
		puts("B.修改学生个人信息");
		puts("C.删除学生个人信息");
		puts("D.查看所有学生个人信息");
		puts("Q.返回图书管理系统");
		puts("请输入选项：按回车键确认，大小写均可");
		puts("所有信息存放在d盘下");
		switch (option = upper_getchar())
		{
			case 'A':add_stu(); break;
			case 'B':modify_stu(); break;
			case 'C':delete_stu(); break;
			case 'D':view_stu(); break;
			case 'Q':break;
			default:puts("\n\n请输入对应操作的英文字母选项！！！");
					system("Pause");
					break;
		}
		system("cls");
	} while (option != 'Q');
}


//添加学生前先查找是否存在重复，然后再添加
void add_stu(void)
{
	char option;//选项
	struct Stu *stu_p1=NULL;
	struct Stu *stu_p2=NULL;
	struct Stu stu;


	puts("请输入学号");
	printf("学号:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",stu.no);
	puts("查找中...");
	if(search_stu(stu.no,&stu_p1,&stu_p2)==1)//重复了
	{
		puts("已有该学生及记录");
		Sleep(1000);
		return;
	}

	puts("请填写该新生详细信息,按回车键录入");

	printf("学号:%s\n",stu.no);
	printf("姓名:_______\b\b\b\b\b\b");
	scanf("%s",&stu.name);
	puts("姓名已录入");
	
	printf("班级:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&stu.class_no);
	puts("班级已录入");

	printf("性别:____\b\b");
	stu.gender=upper_getchar();
	puts("性别已录入");

	printf("联系方式:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&stu.phone_number);
	puts("联系方式已录入");
	
	stu.next=NULL;

	puts("是否保存,输入Y/N，不区分大小写");
	do
	{
		option=upper_getchar();
		if(option=='Y')
		{
			stu_p2=(struct Stu *)malloc(sizeof(struct Stu));
			*stu_p2=stu;
			system("pause");
			if(stu_head==NULL)//空链表
				stu_head=stu_p2;
			else
				stu_p1->next=stu_p2;
			puts("已录入！");
			Sleep(500);
		}
	}while(!(option=='Y'||option=='N'));//必须输入Y/N
}

//修改学生前先查找是否存在
void modify_stu(void)
{
	char option;//选项
	struct Stu stu;
	struct Stu *stu_p1=NULL;
	struct Stu *stu_p2=NULL;

	puts("请输入学号");
	printf("学号:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&stu.no);
	puts("查找中...");
	if(search_stu(stu.no,&stu_p1,&stu_p2)==0)//学生不存在
	{
		Sleep(1000);
		return;
	}

	puts("请填写详细信息,按回车键录入");
	printf("姓名:_______\b\b\b\b\b\b");
	scanf("%s",&stu.name);
	puts("姓名已录入");
	printf("班级:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&stu.class_no);
	printf("班级已录入");
	printf("性别:___\b\b");
	stu.gender=upper_getchar();
	puts("性别已录入");
	printf("联系方式:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&stu.phone_number);
	puts("联系方式已录入");
	puts("是否保存,输入Y/N，不区分大小写");
	stu.next=stu_p2->next;
	do
	{
		option=upper_getchar();
		if(option=='Y')
		{
			//写进去，覆盖，再输入替换
			*stu_p2=stu;
			puts("已录入！");
			Sleep(500);
		}
	}while(!(option=='Y'||option=='N'));
}

//删除学生前，先查找是否存在
void delete_stu(void)
{
	char option;//选项
	struct Stu stu;
	struct Stu *stu_p1=NULL;
	struct Stu *stu_p2=NULL;
	puts("请输入学号");
	printf("学号:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&stu.no);
	puts("查找中...");
	if(search_stu(stu.no,&stu_p1,&stu_p2)==0)//学生不存在
	{
		Sleep(1000);
		return;
	}
	else//一旦找到了，p2指针就在要删除的学生处,p1是p2之前的
	{
		puts("是否删除？输入Y/N，不区分大小写");
		do
		{
			option=upper_getchar();
			if(option=='Y')
			{
				if(stu_p2==stu_head)//链表头
					stu_head=stu_p2->next;
				else
					stu_p1->next=stu_p2->next;
				free(stu_p2);
				puts("删除成功！");
				Sleep(1000);
				return;
			}
		}while(!(option=='Y'||option=='N'));
	}	
}
//查看学生信息
void view_stu(void)
{
	struct Stu *stu_p;
	stu_p=stu_head;
	while(stu_p!=NULL)
	{	
		printf("学号:%s 姓名:%s 班级：%s 性别:%c\n",stu_p->no,stu_p->name,stu_p->class_no,stu_p->gender);
		printf("************************************\n");
		stu_p=stu_p->next;
	}
	system("pause");
}
//********************书籍管理系统*****************
void book_management(void);//书籍管理系统
void add_book(void);//添加新书
void modify_book(void);//修改书籍信息
void delete_book(void);//删除书籍信息
void view_book(void);//查看图书信息

void book_management(void)
{
	char option;
	system("cls");
	do
	{
		puts("************图书信息管理************");
		puts("A.添加新图书信息");
		puts("B.修改图书信息");
		puts("C.删除图书");
		puts("D.查看图书信息");
		puts("Q.返回图书管理系统");
		puts("请输入选项：按回车键确认，大小写均可");
		puts("所有信息存放在d盘下");
		switch (option = upper_getchar())
		{
			case 'A':add_book(); break;
			case 'B':modify_book(); break;
			case 'C':delete_book(); break;
			case 'D':view_book(); break;
			case 'Q':break;
			default:puts("\n\n请输入对应操作的英文字母选项！！！");
					system("Pause");
					break;
		}
		system("cls");
	} while (option != 'Q');
}

//添加图书前先查找是否存在重复，然后再添加
void add_book(void)
{
	
	char option;//选项
	struct Book book;
	struct Book *book_p1=NULL;
	struct Book *book_p2=NULL;
	
	puts("请输入issn编号");
	printf("issn编号:______________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&book.issn);
	puts("查找中...");
	if(search_book(book.issn,&book_p1,&book_p2)==1)//重复了
	{
		puts("已有该书及记录");
		Sleep(1000);
		return;
	}

	strcpy(book.no,"无");//初始化
	puts("请填写该新书详细信息,按回车键录入");
	printf("issn编号:%s\n",book.issn);
	printf("书名:_____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&book.title);
	puts("书名已录入");
	printf("作者:____________\b\b\b\b\b\b\b");
	scanf("%s",&book.author);
	puts("作者已录入");
	printf("出版社:_____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&book.publisher);
	puts("出版社已录入");
	printf("价格:_____\b\b\b\b");
	scanf("%lf",&book.price);
	puts("价格已录入");
	puts("是否保存,输入Y/N，不区分大小写");
	book.next=NULL;
	do
	{
		option=upper_getchar();
		if(option=='Y')
		{
			book_p2=(struct Book *)malloc(sizeof(struct Book));
			*book_p2=book;
			if(book_head==NULL)//空链表
				book_head=book_p2;
			else
				book_p1->next=book_p2;
			puts("已录入！");
			Sleep(500);
		}
	}while(!(option=='Y'||option=='N'));//必须输入Y/N
}

//修改图书前先查找是否存在
void modify_book(void)
{
	char option;//选项
	struct Book book;
	struct Book *book_p1=NULL;
	struct Book *book_p2=NULL;
	

	puts("请输入issn编号");
	printf("issn编号:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&book.issn);
	puts("查找中...");
	if(search_book(book.issn,&book_p1,&book_p2)==0)//学生不存在
	{
		Sleep(1000);
		return;
	}

	//一旦找到了，指针就在此图书信息处
	puts("请填写该新书详细信息,按回车键录入");
	printf("issn编号:%s\n",book.issn);
	printf("书名:_____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&book.title);
	puts("书名已录入");
	printf("作者:____________\b\b\b\b\b\b\b");
	scanf("%s",&book.author);
	puts("作者已录入");
	printf("出版社:_____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&book.publisher);
	puts("出版社已录入");
	printf("价格:_____\b\b\b\b");
	scanf("%lf",&book.price);
	puts("价格已录入");
	book.available=book_p2->available;//初始化
	book.next=book_p2->next;
	puts("是否保存,输入Y/N，不区分大小写");
	do
	{
		option=upper_getchar();
		if(option=='Y')
		{
			//写进去，覆盖，再输入替换
			*book_p2=book;
			puts("已录入！");
			Sleep(500);
		}
	}while(!(option=='Y'||option=='N'));
}

//删除图书前，先查找是否存在
void delete_book(void)
{
	char option;//选项
	struct Book book;
	struct Book *book_p1=NULL;
	struct Book *book_p2=NULL;

	puts("请输入issn编号");
	printf("issn编号:______________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&book.issn);
	puts("查找中...");
	if(search_book(book.issn,&book_p1,&book_p2)==0)//图书不存在
	{
		Sleep(1000);
		return;
	}
	else//一旦找到了，p2指针就在要删除的图书处
	{
		puts("是否删除？输入Y/N，不区分大小写");
		do
		{
			option=upper_getchar();
			if(option=='Y')
			{
				if(book_p2==book_head)//链表头
					book_head=book_p2->next;
				else
					book_p1->next=book_p2->next;
				free(book_p2);
				puts("删除成功！");
				Sleep(1000);
				return;
			}
		}while(!(option=='Y'||option=='N'));
	}
}
//查看图书信息
void view_book(void)
{
	struct Book *book_p;
	book_p=book_head;
	while(book_p!=NULL)
	{
		printf("书名：%s issn编号：%s \n出版社：%s 作者：%s \n价格：%lf \n",
			book_p->title,book_p->issn,
			book_p->publisher,book_p->author,
			book_p->price);
		printf("************************************\n");
		book_p=book_p->next;
	}
	system("pause");
}

//**********************借/还书********************
void borrow_or_return_book(void);
void borrow_book(void);//借书
void return_book(void);//还书

void borrow_or_return_book(void)
{
	char option;
	system("cls");
	do
	{
		puts("************借/还书************");
		puts("A.借书");
		puts("B.还书");
		puts("Q.返回图书管理系统");
		puts("请输入选项：按回车键确认，大小写均可");
		switch (option = upper_getchar())
		{
			case 'A':borrow_book(); break;
			case 'B':return_book(); break;
			case 'Q':break;
			default:puts("\n\n请输入对应操作的英文字母选项！！！");
					system("Pause");
					break;
		}
		system("cls");
	} while (option != 'Q');
}
void borrow_book(void)//借书
{
	char option;//选项
	struct Stu stu;
	struct Stu *stu_p1=NULL;
	struct Stu *stu_p2=NULL;

	struct Book book;
	struct Book *book_p1=NULL;
	struct Book *book_p2=NULL;

	struct History history;
	struct History *history_p1=NULL;
	struct History *history_p2=NULL;

	puts("请输入学号");
	printf("学号:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&stu.no);
	puts("查找中...");
	if(search_stu(stu.no,&stu_p1,&stu_p2)==0)//学生不存在
	{
		Sleep(1000);
		return;
	}
	puts("请输入图书的issn编号");
	printf("issn编号:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&book.issn);
	puts("查找中...");
	if(search_book(book.issn,&book_p1,&book_p2)==0)//图书不存在
	{
		Sleep(1000);
		return;
	}

	if(book_p2->available=='N')
	{
		puts("此图书已经被借走！");
		system("pause");
		return;//函数结束
	}
	search_history(stu.no,book.issn,&history_p1,&history_p2);
	book=*book_p2;
	book.available='N';//借走了
	strcpy(book.no,stu.no);
	puts("请输入借书时间");
	scanf("%d%d%d",&history.borrow_date.year,&history.borrow_date.month,&history.borrow_date.day);
	strcpy(history.issn,book.issn);
	strcpy(history.no,stu.no);
	history.penalty=0;
	history.return_date.day=0;
	history.return_date.month=0;
	history.return_date.year=0;
	history.next=NULL;
	puts("是否借书,输入Y/N，不区分大小写");
	do
	{
		option=upper_getchar();
		if(option=='Y')
		{
			*book_p2=book;
			history_p2=(struct History *)malloc(sizeof(struct History));
			*history_p2=history;
			if(history_head==NULL)//空链表
				history_head=history_p2;
			else
				history_p1->next=history_p2;
			puts("已录入！");
			Sleep(500);
		}
	}while(!(option=='Y'||option=='N'));
}


void return_book(void)
{

	char option;//选项
	struct History history;
	struct Book book;
	struct History *history_p1=NULL;
	struct History *history_p2=NULL;
	struct Book *book_p1=NULL;
	struct Book *book_p2=NULL;

	puts("请输入学号");
	printf("学号:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&history.no);
	puts("请输入图书的issn编号");
	printf("issn编号:___________\b\b\b\b\b\b\b\b\b\b");
	scanf("%s",&history.issn);
	puts("查找中...");
	if(search_history(history.no,history.issn,&history_p1,&history_p2)==0)//记录不存在
	{
		Sleep(1000);
		return;
	}
	history=*history_p2;
	search_book(history.issn,&book_p1,&book_p2);
	book=*book_p2;
	book.available='Y';//初始化
	strcpy(book.no,"无");//初始化
	puts("请输入还书时间");
	scanf("%d%d%d",&history.return_date.year,&history.return_date.month,&history.return_date.day);
	if(cal_date(history.borrow_date,history.return_date)-DEADLINE>0)//超过还书日期了
		history.penalty=(cal_date(history.borrow_date,history.return_date)-DEADLINE)*PENALTY;
	else
		history.penalty=0;
	puts("是否还书,输入Y/N，不区分大小写");
	do
	{
		option=upper_getchar();
		if(option=='Y')
		{	
			*book_p2=book;
			*history_p2=history;
			puts("已录入！");
			if(history.penalty)
				printf("本次借书逾期！\n罚金：%lf",history.penalty);
			system("pause");
		}
	}while(!(option=='Y'||option=='N'));
}
//*********************主函数*********************
int main(void)
{
	char option;
	read_file();
	printf("            欢 ");
	Sleep(500);
	printf("迎 ");
	Sleep(500);
	printf("使 ");
	Sleep(500);
	printf("用 ");
	Sleep(500);
	printf("图 ");
	Sleep(500);
	printf("书 ");
	Sleep(500);
	printf("管 ");
	Sleep(500);
	printf("理 ");
	Sleep(500);
	printf("系 ");
	Sleep(500);
	printf("统 ");
	Sleep(500);
	system("cls");
	do
	{
		puts("************图书管理系统************");
		puts("A.学生信息管理");
		puts("B.图书信息管理");
		puts("C.借/还书");
		puts("D.综合查询");
		puts("E.清空数据/初始化");
		puts("Q.退出");
		puts("请输入选项：按回车键确认，大小写均可");
		switch (option = upper_getchar())
		{
		case 'A':stu_management(); write_file();break;
		case 'B':book_management(); write_file();break;
		case 'C':borrow_or_return_book();write_file(); break;
		case 'D':query();break;
		case 'E':freeall();initialization();break;
		case 'Q':break;
		default:puts("\n\n请输入对应操作的英文字母选项！！！");
				system("Pause");
				break;
		}
		system("cls"); //下一次操作清屏
	} while (option != 'Q');
	freeall();
	for(int i=0;i<6;i++)//退出特效
	{
		for(int j=0;j<i;j++)
			printf("\n");
		puts("感谢使用！");
		Sleep(500);
		system("cls");
	}
	return 0;
}
