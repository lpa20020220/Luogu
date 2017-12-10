#include<bits/stdc++.h>
using namespace std;
struct node
{
    node *fail;
    node *nextt[26];
    int indi;
};
node *root; node *newnode;
char target[1000005];
char mode[155][155];
struct sd
{
    int number;
    int sum;
}record[155];
bool cmp(sd a,sd b)
{
    if(a.sum>b.sum )return true;
    if(a.sum==b.sum &&a.number <b.number )return true;
    return false;
}
inline void insertit(int num)
{
    node *now=root;
    int value;
    int len=strlen(mode[num]);
    for(register int i=0;i<len;++i)
    {
    	value=mode[num][i]-'a';
    	if(now->nextt[value]==NULL)
    	{
    		newnode=new node;
    		for(register int i=0;i<=25;++i)
    		{
    			newnode->nextt [i]=NULL;
    		}
    		newnode->fail =NULL;
    		newnode->indi =0;
    		now->nextt[value]=newnode;
    	}
    	now=now->nextt[value];
    }
    now->indi=num;
}
void getfail()
{
    node *now;node *back;
    queue<node *> q;
    q.push(root);
    while(!q.empty())
    {
        now=q.front();
        q.pop();
        for(register int i=0;i<26;++i)
        {
            if(now->nextt[i])
            {
                if(now==root)
                {
                    now->nextt[i]->fail=root;
                }
                else
                {
                    back=now->fail;
                    while(back)
                    {
                        if(back->nextt[i])
                        {
                            now->nextt[i]->fail=back->nextt[i];
                            break;
                        }
                        back=back->fail;
                    }
                    if(back==NULL)
                    {
                        now->nextt[i]->fail=root;
                    }
                }
                q.push(now->nextt[i]);
            }
        }
    }
}
void AC()
{
    node *now=root; node *back;
    int value;
    int len=strlen(target);
    for(register int i=0;i<len;++i)
    {
        value=target[i]-'a';
        while(now!=root&&!now->nextt[value])
        now=now->fail;
        now=now->nextt[value];
        if(now==NULL)now=root;
        back=now;
        while(back!=NULL)
        {
            if(back->indi!=0)
            {
                record[back->indi].sum ++;
            //	printf("now  %d  %s\n",i,mode[back->indi]);
            }
            //else break;
            back=back->fail;
        }
    }
}
void print(int num)
{
    sort(record+1,record+1+num,cmp);
    int mx=record[1].sum ;
    printf("%d\n",mx);
    for(int i=1;i<=num;i++)
    {
        if(record[i].sum==mx)
        printf("%s\n",mode[record[i].number]);
    }
}
int main()
{
    //freopen("haha.in","r",stdin);
    int n;
    while(true)
    {
    root=new node;
    for(int i=0;i<26;++i)
    root->nextt[i]=NULL;
    root->fail =NULL;
    root->indi =0;
    scanf("%d",&n);
    if(n==0)break;
    for(register int i=1;i<=n;++i)
    {
        scanf("%s",mode[i]);
        record[i].number =i;
        record[i].sum =0;
        insertit(i);
    }
    scanf("%s",target);
    getfail();
    AC();
    print(n);
    }
    return 0;
}
