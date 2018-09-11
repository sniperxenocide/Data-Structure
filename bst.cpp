#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    static int cnt=0;
    if(node!=0)getSize(node->left);
    if(node!=0)getSize(node->right);
    if(node==0) return 0;
    else
    {
        cnt++;
        return cnt;
    }
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    struct treeNode *temp;
    temp=root;
    int depth=0;
    while(1)
    {
        if(temp==node) return depth;
        else
        {
            if(node->item<temp->item) temp=temp->left;
            else temp=temp->right;
            depth++;
        }
    }
}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode *temp;
    temp=root;
    int depth=0;
    while(1)
    {
        if(temp->item==item) return depth;
        else
        {
            if(item<temp->item) temp=temp->left;
            else temp=temp->right;
            depth++;
        }
    }
}



struct treeNode* findSuccessor(struct treeNode * node, int item)
{
    struct treeNode * succ, * t;
    if( node->right != 0 )
    {
        succ = node->right ;
        while( succ->left!=0 ) succ = succ->left ;
        return succ ;
    }
    else
    {
        succ = 0 ;
        t = root ;
        while( t!= 0 )
        {
            if (node->item == t->item ) return succ ;
            else if (node->item < t->item )
            {
                succ = t ;
                t = t->left ;
            }
            else t = t->right ;
        }
        return 0 ;
    }
}

int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    struct treeNode *temp=root,*parent,*succ;
    if(root->item==item)
    {
        if(root->left==0 && root->right==0) {free(root);return TRUE_VALUE;}
        else if(root->right==0)
        {
            temp=root;
            root=root->left;
            free(temp);
            return TRUE_VALUE;
        }
        else
        {
            temp=root;
            succ=temp->right;
            parent=temp;
            while(succ->left!=0)
            {
                parent=succ;
                succ=succ->left;
            }
            int t=succ->item;
            succ->item=temp->item;
            temp->item=t;
            if(succ->left==0 && succ->right==0)
            {
                if(parent->left==succ) parent->left=0;
                else parent->right=0;
                free(succ);
                return TRUE_VALUE;
            }
            else
            {
                if(parent->left==succ) parent->left=succ->right;
                else parent->right=succ->right;
                free(succ);
                return TRUE_VALUE;
            }
        }
    }
    while(1)
    {
        parent=temp;
        //if(parent->left->item==item) {temp=temp->left; break;}
        //else {temp=temp->right; break;}
        if(item<temp->item) temp=temp->left;
        else temp=temp->right;
        if(temp->item==item) break;
    }
    if(temp->left==0 && temp->right==0)
    {
        if(parent->left==temp) parent->left=0;
        else parent->right=0;
        free(temp);
        return TRUE_VALUE;
    }
    else if(temp->left==0 && temp->right!=0)
    {
        if(parent->left==temp) parent->left=temp->right;
        else parent->right=temp->right;
        free(temp);
        return TRUE_VALUE;
    }
    else if(temp->left!=0 && temp->right==0)
    {
        if(parent->left==temp) parent->left=temp->left;
        else parent->right=temp->left;
        free(temp);
        return TRUE_VALUE;
    }
    else if(temp->left!=0 && temp->right!=0)
    {
        succ=temp->right;
        parent=temp;
        while(succ->left!=0)
        {
            parent=succ;
            succ=succ->left;
        }
        int t=succ->item;
        succ->item=temp->item;
        temp->item=t;
        if(succ->left==0 && succ->right==0)
        {
            if(parent->left==succ) parent->left=0;
            else parent->right=0;
            free(succ);
            return TRUE_VALUE;
        }
        else{
            if(parent->left==succ) parent->left=succ->right;
            else parent->right=succ->right;
            free(succ);
            return TRUE_VALUE;
        }
    }
    //return FALSE_VALUE;
}



int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    struct treeNode *node;
    node=root;
    if(node==0) return FALSE_VALUE;
    while(1)
    {
        if(node->left==0)
        {
            return node->item;
        }
        else
        {
            node=node->left;
        }
    }
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    struct treeNode *node;
    node=root;
    if(node==0) return FALSE_VALUE;
    while(1)
    {
        if(node->right==0)
        {
            return node->item;
        }
        else
        {
            node=node->right;
        }
    }
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    //write your codes here
    static int cnt=0;
    if(node!=0)rangeSearch(node->left,leftBound,rightBound);
    if(node!=0)rangeSearch(node->right,leftBound,rightBound);
    if(node==0) return 0;
    else
    {
        if(node->item>=leftBound && node->item<=rightBound) cnt++;
        return cnt;
    }
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    int i10=0;
    int i11=0;
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6.itemDepth. 7.nodeDepth. 8.getMax. 9.getMin\n10.getSize. 11.rangeSearch ");
        printf("12. PrintInOrder. 13. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int item;
            printf("item:");
            scanf("%d", &item);
            int i=calcDepth(item);
            printf("depth: %d\n",i);
        }
        else if(ch==7)
        {
            int item;
            printf("item:");
            scanf("%d", &item);
            int i=calcNodeDepth(searchItem(root,item));
            printf("depth: %d\n",i);
        }
        else if(ch==8)
        {
            int i=getMaxItem();
            printf("Max: %d\n",i);
        }
        else if(ch==9)
        {
            int i=getMinItem();
            printf("Min: %d\n",i);
        }
        else if(ch==10)
        {
            printf("Size: %d\n",getSize(root)-i10);
            i10=getSize(root);
        }
        else if(ch==11)
        {
            int a,b;
            printf("left:");
            scanf("%d",&a);
            printf("right:");
            scanf("%d",&b);
            printf("Total item: %d\n",rangeSearch(root,a,b)-i11);
            i11=rangeSearch(root,a,b);
        }
        else if(ch==12)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==13)
        {
            break;
        }
    }

}
