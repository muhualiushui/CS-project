/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
    for(auto i=0;i<num;i++){
        set.push_back(set.size());
    }
}
int DisjointSets::find(int elem){
    if(set[elem]>=0&&set[elem]!=elem){
        return find(set[elem]);
    }
    return elem;
}
void DisjointSets::setunion(int a, int b){
    int root1=0;
    int root2=0;
    if(set[a]==a){
        set[a]=-1;
    }
    if(set[b]==b){
        set[b]=-1;
    }
    root1=(set[a]<0)? a:find(a);
    root2=(set[b]<0)? b:find(b);
    int new_size=set[root1]+set[root2];
    if(set[root1]<=set[root2]){
        set[root1]=new_size;
        set[root2]=root1;
    }else{
        set[root2]=new_size;
        set[root1]=root2;
    }
}

int DisjointSets::size(int elem){
    if(set[elem]==elem){
        return 1;
    }
    int root=find(elem);
    return set[root]*(-1);
}