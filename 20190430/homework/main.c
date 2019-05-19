#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="root";
    char* password="123456";
    char* database="test";
    char query[300]={0};
    int t;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
        return -1;
    }else{
        printf("Connected...\n");
    }
    printf("学生信息：\n");
    strcpy(query,"select * from student");
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));
    }else{
        res=mysql_use_result(conn);
        if(res)
        {
            while((row=mysql_fetch_row(res))!=NULL)
            {
                for(t=0;t<mysql_num_fields(res);t++)
                {
                    printf("%8s ",row[t]);
                }
                printf("\n");
            }
        }else{
            printf("Don't find data\n");
        }
        mysql_free_result(res);
    }
    printf("选课信息：\n");
    strcpy(query,"select * from course");
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));
    }else{
        res=mysql_use_result(conn);
        if(res)
        {
            while((row=mysql_fetch_row(res))!=NULL)
            {
                for(t=0;t<mysql_num_fields(res);t++)
                {
                    printf("%8s ",row[t]);
                }
                printf("\n");
            }
        }else{
            printf("Don't find data\n");
        }
        mysql_free_result(res);       
    }
    int c_id,s_id;
    printf("请输入选课信息：\n");
    printf("学号：");fflush(stdout);
    scanf("%d",&s_id);
    printf("课程：");fflush(stdout);
    scanf("%d",&c_id);
    printf("\n");
    memset(query,0,sizeof(query));
    sprintf(query,"insert into selection(studentID,courseID) values(%d,%d)",s_id,c_id);
    printf("%s\n",query);
    t=mysql_query(conn,query);
    if(t){
        printf("Error making query:%s\n",mysql_error(conn));
    }else{
        printf("insert success\n");
    }
    mysql_close(conn);
    return 0;
}
