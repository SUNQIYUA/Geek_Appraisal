#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���ҽ��i�ĸ����,ͨ���ݹ�õ���㵽���ĳ���
int findParent(int i,int huffman[][4],int n);
//���ݳ�ʼȨ�ع�����������
void huffmanTree(int w[],int huffman[][4],int n);
//Ѱ��Ȩ����С�������ڵ�
void findMin(int ii[],int huffman[][4],int n);
//��ÿ��Ҷ�ڵ���й���������
void HuffmanCode(int i,int huffman[][4],int n);
//��������char������
void inplace_swap(char *x,char *y);

int main()
{
    //��������ַ������м�¼�����ַ����ܸ���count�Լ������ַ��ĳ��ִ���arr_small[]����ͳ��
    char str[100];
    printf("Please Enter the string\n");
    scanf("%s", str);
    int arr_big[27] = {0};  //�����ַ��ĳ��ִ���
    int count = 0;  //�ַ����ܸ���
    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K',';L','M','N','O','P','R','S','T','U','V','W','X','Y','Z'};
    for(int i = 0; i < strlen(str); i++)    //���������ַ����е������ַ�
    {
        for(int j = 0; j < 27; j++) //����26����д��ĸ
        {
            if(str[i] == alphabet[j])
            {
                arr_big[j] += 1;
                if(arr_big[j] == 1)
                  count++;
                  break;
                
            }
        }
    }
    printf("the letter count is %d\n",count);   //��ӡ�����ַ��������˼�����ĸ

    //ͨ��arr_big�������ַ����г��ֵ���ĸ��������ͳ�ƣ���������arr_small��
    int count2 = 0;    //�ַ����г��ֵ��ַ��ܸ���
    int arr_small[count] ; 
	for(int i = 0; i < 27; i++)
    {
        if(arr_big[i] != 0 && count2 < count)
        {
            arr_small[count2] = arr_big[i];
			count2++;	//������arr_big�еķ��������θ���arr_small���Դ˱�ʾ����ĸ���ִ���
        }
    }//ͳ�������ַ�������ĸ�ĳ��ִ���
    printf("the small count %d is %d\n ", count2, arr_small[count2-1]);
   
    //����int�Ͷ�ά���飬���鳤��[*]Ϊ���������Ľڵ����
    //c[*][0]��ŵ��Ǹýڵ��[���ڵ��λ��]��c[*][1]Ϊ�ýڵ��[�������ڵ��λ��]
    //c[*][2]��Ÿýڵ��[�������ڵ��λ��]��c[*][3]Ϊ�ýڵ��Ȩֵ
    int huffman[2 * count - 1][4];  //ǰn��ΪҶ��㣬��n-1��Ϊ�м���

    //���ݳ�ʼȨ������arr_small���ַ���������huffman��
    huffmanTree(arr_small,huffman,count);

    //����Huffman���������ܳ���WPL
    int sum = 0;
    for(int i = 0;i < count;i++)
    {
        int length = 0;
        if(huffman[i][1] == -1 && huffman[i][2] == -1)  //�����������ڵ� 
        {
            length = findParent(i,huffman,count);   //�õ�����Ҷ���Ĵ�Ȩ·������
            sum += length;	//����Ҷ����Ȩ·�������ۼӵõ��ܳ���WPL
        }
    }
    printf("the tree's WPL  is  %d\n",sum);

    //Huffman����
    for(int i = 0;i < count;i++)
    {
        HuffmanCode(i,huffman,count);
    }

    return 0;
}

//�Ӻ�������������������
void huffmanTree(int w[],int huffman[][4],int n)
{
    //����ʼ��
    for(int i = 0; i < 2 * n - 1; i++)
    {
        huffman[i][0] = -1;
        huffman[i][1] = -1;
        huffman[i][2] = -1;
        huffman[i][3] = -1;
    }
    /*����ʼ��㸳����ά������*/
    for(int i = 0; i < n; i++)
    {
        huffman[i][3] = w[i];
    }
    //ÿ�γ������Ȩ����С�Ľ����кϲ���ֱ�����ղ��������
    for(int i = n; i < 2 * n - 1; i++)
    {
        int i1,i2;  //Ȩ����С���������
        int ii[2]; 
        //�ҳ�����Ȩ����С�Ľ��
        findMin(ii,huffman,n);
        i1=ii[0];
        i2=ii[1];
        //�ϲ�i1��i2���,���½����Ϣ�������ɽ��������ӽ�㣬�ӽڵ��Ӧ�ĸ���㣬�����ɽ���Ȩ�أ�
        
        huffman[i1][0] = huffman[i2][0] = i;
        huffman[i][1] = i1;
        huffman[i][2] = i2;
        huffman[i][3] = huffman[i1][3] + huffman[i2][3];
        
        
    }
}

//�Ӻ��������ҳ�����Ȩ����С�Ľ��
void findMin(int ii[],int huffman[][4],int n)
{
    //�ҳ���һ��Ȩ����С�Ľ��
    int min1 = 9999999;
    for(int i = 0; i < 2 * n - 1; i++)
    {
        if(huffman[i][3] == -1 && huffman[i][0] == -1)  //�ж��Ƿ���ڸ����y�Լ��Ƿ�Ϊ��ʼ��� 
        {
            break;
        }
        if(huffman[i][3] < min1 && huffman[i][0] == -1)  //�ȽϽ���С���жϸý���Ƿ���С 
        {
            min1 = huffman[i][3];
            ii[0] = i;
        }
    }

     int min2 = 9999999;
    for(int j = 0; j < 2 * n - 1; j++)
    {
        if(huffman[j][3] == -1 && huffman[j][0] == -1)  
        {
            break;
        }
        if(huffman[j][3] < min2 && huffman[j][0] == -1 && j != ii[0]) 
        {
            min2 = huffman[j][3];
            ii[1] = j;
        }
    }
    
   
    
}

//�Ӻ����������ҽ��i�ĸ����,�õ���㵽���ĳ���
int findParent(int i,int huffman[][4],int n)
{
    int length = 0;
    if(huffman[i][0] == -1)     /*�Ƿ���ڸ����*/
    {
        return 0;
    }
    length += (findParent(huffman[i][0],huffman,n) + 1);    //ͨ���ݹ�õ���㵽����·������
    return length;
}

//�Ӻ���������ÿ��Ҷ�ڵ���й��������벢���д�ӡ
void HuffmanCode(int i,int huffman[][4],int n)
{
    char code[30];  //char����������
    int current=i;  //���嵱ǰ���ʵĽ��
    int father = huffman[i][0]; //���嵱ǰ���ĸ��ڵ�
    int start=0;    //ÿ�α����λ�ã���ʼΪ���뵹��λ��
    int first,last; //char�����ͷ����β��

    while(father != -1)
    {
       	
		if(huffman[father][1] == current)//�жϵ�ǰ���ĸ�����������Ƿ�Ϊ��ǰ���
       	code[start] = '0';	  //�ӽ���Ǹ�����������������Ϊ0
        if(huffman[father][2] == current)
		code[start] = '1';		//�ӽ���Ǹ�����������������Ϊ1

        current = huffman[current][0];	//����˷Դ�����µ�ǰ���
        father = huffman[current][0];		//ͬ������ǰ�����º󣩣����µ�ǰ���ĸ��׽��
       	start++;//���±���λ��
    }
    	code[start]='\0';    //���������

      
      //�Ե������ڲ�Ԫ�� 

    //��char�����е�Ԫ��ͷβ���˽��жԵ�
    for(first = 0, last = start-1; first < last; first++,last--)
    {
        
        inplace_swap(&code[first], &code[last]);	/*�ú������Լ���д*/
    }

    printf("%c Huffman code:  %s\n",'A'+i,code);    //��ӡ�ַ���huffman����
}

//�Ӻ���������������char�����ݣ�ʹ���˲������㣩�����Լ������ÿɶ��ԽϺõķ�������ʵ�ָĺ���
void inplace_swap(char *x,char *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}
