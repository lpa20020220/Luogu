#include<bits/stdc++.h>
using namespace std;
struct node
{
	int sum;
	node *nextt[26];
	node *fail;
};
node* root;node *newnode;
node x;
char tar[1000005];
char data[1000005];
inline void build_trie()
{
	node *p=root;
	int now;
	int lent=strlen(tar);
	for(register int i=0;i<lent;i++)
	{
		now=tar[i]-'a';
		if(p->nextt[now]==NULL)
		{
			newnode=new node;
			for(int i=0;i<26;i++)newnode->nextt[i]=NULL;
			newnode->sum=0;
			newnode->fail=NULL;
			p->nextt[now]=newnode;
		}
		p=p->nextt [now];
	}
	p->sum++;
}
inline void getfail()
{
	queue<node *>q;
	node * p;node *temp;
	q.push(root);
	while(!q.empty())
	{
		temp=q.front();
		q.pop();
		for(int i=0;i<26;i++)
		{
			if(temp->nextt[i])
			{
				if(temp==root)
				{
					temp->nextt[i]->fail=root;
				}
				else
				{
					p=temp->fail;
					while(p)
					{
						if(p->nextt[i])
						{
							temp->nextt[i]->fail=p->nextt[i];
							break;
						}
						p=p->fail;
					}
					if(p==NULL)
					{
						temp->nextt[i]->fail=root;
					}
				}
				q.push(temp->nextt[i]);
			}
		}
	}
}
int ans=0;
void AC()
{
	node *p=root;
	node *temp;
	int lend=strlen(data);
	int now;
	for(register int i=0;i<lend;i++)
	{
		now=data[i]-'a';
		while(!p->nextt[now]&&p!=root)
		{
			p=p->fail;
		}
		p=p->nextt [now];
		if(!p)p=root;
		temp=p;
		while(temp!=root)
		{
			if(temp->sum >=0)
			{
				ans+=temp->sum;
				temp->sum =-1;
			}
			else break;
			temp=temp->fail ;
		}
	}
} 
int main()
{
	root=&x;
	int num;
	scanf("%d",&num);
	for(int i=1;i<=25;i++)root->nextt[i]=NULL;
	for(int i=1;i<=num;i++)
	{
		scanf("%s",tar);
		build_trie();
    }
    scanf("%s",data);
    getfail();
    AC();
    printf("%d",ans);
    return 0;
}
