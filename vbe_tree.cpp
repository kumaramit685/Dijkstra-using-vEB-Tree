
//APS Project 
//Team A
// Nalini & Amit
//Dijikstra using van Emde Boas Tree (VEB_Tree) 
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <time.h>

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>

using namespace std;

typedef unsigned long long veb_ull;

///Defining the VEB Tree////////////

class VEB_Tree
{
    veb_ull sizeu;
   
///for finding the minimum and maximum///////////
 
    veb_ull *vmin, *vmax;
    VEB_Tree *sarray;   
    VEB_Tree **sbunch;  
    
public:

    VEB_Tree(veb_ull);
    //for finding whether the member of tree or not//////

    bool veb_mem(veb_ull);
/////////////for the insertion of an element

    void ele_in(veb_ull);
/////////////for the deletion of an element
    void ele_Del(veb_ull);

///function for finding the minimum value
    veb_ull value_min();

///function for finding the maximum value
    veb_ull value_max();

/// for finding the predecessor of given number
    veb_ull* predecessor(veb_ull);

/// for finding the successor of given number
    veb_ull* successor(veb_ull);
    
    veb_ull findMin();
    veb_ull val_one();
    void minusKey(veb_ull, veb_ull);
};

VEB_Tree::VEB_Tree(veb_ull sizeu)
{

///Initializing the values//////////////

    this -> sizeu = sizeu;
    this -> vmin = NULL;
    this -> vmax = NULL;
    
    if (sizeu == 2)
    {
        this -> sarray = NULL;
        this -> sbunch = NULL;
    }
    
    else
    {
        veb_ull size_s1 = (veb_ull)sqrt(sizeu);
////sum array of veb
        this -> sarray = new VEB_Tree(size_s1);
////sub group or cluster

        this -> sbunch = new VEB_Tree*[size_s1];
    }
}

/////finding the veb member or not///////////

bool VEB_Tree::veb_mem(veb_ull valx)
{
    if (sizeu == 2)
    {
        if (vmin == NULL) return false;

//if valuex = 0 the it is the minimum
        if (valx == 0) return ((*vmin) == 0);

//if valuex is 1 then it is the max
        else if (valx == 1) return ((*vmax) == 1);
        return false;
    }
    else
    {
        if (vmin == NULL) return false;
        if (valx < (*vmin) || valx > (*vmax)) return false;
        else if (valx == (*vmin) || (valx == (*vmax))) return true;
        else
        {
            veb_ull size_s1 = (veb_ull)sqrt(sizeu);

            veb_ull high = valx / size_s1, low = valx % size_s1;
            if (sbunch[high] == NULL) return false;
            else return sbunch[high] -> veb_mem(low);
        }

    }
}

/////////////////// Insertion of elements in the veb tree///////////////

void VEB_Tree::ele_in(veb_ull valx)
{
    if (sizeu == 2)

/////////////////only 2 elements////////////////
    {
        if (valx == 0)
        {
            if (vmin == NULL)
            {
                vmin = new veb_ull;
                vmax = new veb_ull;

	////both values are pointing to same value
                (*vmin) = (*vmax) = valx;
            }
            else (*vmin) = valx;
        }
        else if (valx == 1)
        {
            if (vmax == NULL)
            {
                vmin = new veb_ull;
                vmax = new veb_ull;
                (*vmin) = (*vmax) = valx;
            }
            else (*vmax) = valx;
        }
    }
    else
    {
        if (vmin == NULL)
        {
            vmin = new veb_ull;
            vmax = new veb_ull;
            (*vmin) = (*vmax) = valx;
        }
        else
        {
            if (valx < (*vmin))
            {
                veb_ull sortMin = (*vmin);
                (*vmin) = valx;
                this -> ele_in(sortMin);
            }
            else
            {
                veb_ull size_s1 = (veb_ull)sqrt(sizeu);
                veb_ull high = valx / size_s1, low = valx % size_s1;
                if (sbunch[high] == NULL)
                {
                    sbunch[high] = new VEB_Tree(size_s1);
                    sbunch[high] -> ele_in(low);
                    sarray -> ele_in(high);
                }
                else sbunch[high] -> ele_in(low);
                
                if (valx > (*vmax)) (*vmax) = valx;
            }
        }
    }
}

////////////////////////Deletion of an element from the veb/////////////////

void VEB_Tree::ele_Del(veb_ull valx)
{
    if (sizeu == 2)
    {
        if (valx == 0)
        {
            if ((*vmax) == 0)
            {
                vmin = vmax = NULL;
            }
            else (*vmin) = 1;
        }
        else if (valx == 1)
        {
            if ((*vmin) == 1)
            {
                vmin = vmax = NULL;
            }
            else (*vmax) = 0;
        }
    }
    else
    {
        veb_ull size_s1 = (veb_ull)sqrt(sizeu);
        veb_ull high = valx / size_s1, low = valx % size_s1;
        
        if (valx == (*vmin))
        {
            if (valx == (*vmax))
            {
                vmin = vmax = NULL;
            }
            else
            {
                veb_ull n_high = sarray -> value_min();
                veb_ull n_Low = sbunch[sarray -> value_min()] -> value_min();
                veb_ull n_Min = n_high * size_s1 + n_Low;
                this -> ele_Del(n_Min);
                (*vmin) = n_Min;
            }
        }
        else
        {
            sbunch[high] -> ele_Del(low);
            if (sbunch[high] -> vmin == NULL)
            {
                sarray -> ele_Del(high);
                delete sbunch[high];
                sbunch[high] = NULL;
            }
            if (valx == (*vmax))
            {
                if (sarray -> vmin == NULL) (*vmax) = (*vmin);
                else
                {
                    veb_ull nm_high = sarray -> value_max();
                    veb_ull nm_Low = sbunch[sarray -> value_max()] -> value_max();
                    (*vmax) = nm_high * size_s1 + nm_Low;
                }
            }
        }
    }
}

///////////////////////Finding the Minimum value

veb_ull VEB_Tree::value_min()
{
    return (*vmin);
}

/////////////////////////Finding the Maximum value

veb_ull VEB_Tree::value_max()
{
    return (*vmax);
}

//////////////////////Finding the Predecessor

veb_ull* VEB_Tree::predecessor(veb_ull valx)
{
    if (sizeu == 2)
    {
        if (valx == 0) return NULL;
        else if (valx == 1)
        {
            if (vmin == NULL) return NULL;
            if ((*vmin) == 1) return NULL;
            return vmin;
        }
        else return NULL;
    }
    else
    {
        if (vmin == NULL) return NULL;
        if (valx <= (*vmin)) return NULL;
        if (valx > (*vmax)) return vmax;

        veb_ull size_s1 = (veb_ull)sqrt(sizeu);
        veb_ull high = valx / size_s1;
        veb_ull low = valx % size_s1;

        if (sbunch[high] == NULL)
        {
            veb_ull* previous = sarray -> predecessor(high);
            veb_ull* val_ret = new veb_ull;
            (*val_ret) = (*previous) * size_s1 + sbunch[(*previous)] -> value_max();
            return val_ret;
        }
        else
        {
            veb_ull *new_Low, *new_high;
            new_high = new veb_ull;
            new_Low = new veb_ull;
            (*new_high) = high;
            veb_ull minInsbunch = sbunch[high] -> value_min();
            if (low > minInsbunch) new_Low = sbunch[high] -> predecessor(low);
            else
            {
                new_high = sarray -> predecessor(high);
                (*new_Low) = sbunch[(*new_high)] -> value_max();
            }
            veb_ull *val_ret = new veb_ull;
            (*val_ret) = (*new_high) * size_s1 + (*new_Low);
            return val_ret;
        }
    }
}

/////////////////////////Finding the successor of the value given

veb_ull* VEB_Tree::successor(veb_ull valx)
{
    if (sizeu == 2)
    {
        if (valx == 1) return NULL;
        else if (valx == 0)
        {
            if (vmax == NULL) return NULL;
            if ((*vmax) == 0) return NULL;
            return vmax;
        }
        else return NULL;
    }
    else
    {
        if (vmin == NULL) return NULL;
        if (valx >= (*vmax)) return NULL;
        if (valx < (*vmin)) return vmin;

        veb_ull size_s1 = (veb_ull)sqrt(sizeu);
        veb_ull high = valx / size_s1;
        veb_ull low = valx % size_s1;

        if (sbunch[high] == NULL)
        {
            veb_ull* next = sarray -> successor(high);
            veb_ull* val_ret = new veb_ull;
            (*val_ret) = (*next) * size_s1 + sbunch[(*next)] -> value_min();
            return val_ret;
        }
        else
        {
            veb_ull *new_Low, *new_high;
            new_high = new veb_ull;
            new_Low = new veb_ull;
            (*new_high) = high;
            veb_ull maxInsbunch = sbunch[high] -> value_max();
            if (low < maxInsbunch) new_Low = sbunch[high] -> successor(low);
            else
            {
                new_high = sarray -> successor(high);
                (*new_Low) = sbunch[(*new_high)] -> value_min();
            }
            veb_ull *val_ret = new veb_ull;
            (*val_ret) = (*new_high) * size_s1 + (*new_Low);
            return val_ret;
        }
    }
}

///////////////////////Extracting the minimum value///////////////

veb_ull VEB_Tree::findMin()
{
    veb_ull val_ret = this -> value_min();
    this -> ele_Del(val_ret);
    return val_ret;
}

//////////////////////Finding the first value/////////////////////

veb_ull VEB_Tree::val_one()
{
    return this -> value_min();
}

//////////////////////Decreasing the value///////////////

void VEB_Tree::minusKey(veb_ull valx, veb_ull valy)
{
   
    
    this -> ele_Del(valx);
    this -> ele_in(valy);
}

////////////////////////main ///////////////////////////

int main()
{
cout<<"Enter the Number of numbers to be Inserted:"<<endl;
int N;
int veb_num_srh;
int veb_num_del;
cin>> N;
    VEB_Tree *VEB_Tree = new class VEB_Tree(16);
   
cout<<"Enter the Numbers to be Inserted:"<<endl;
int i;
for (i=0;i<N;i++)
{   
int veb_num_in;
cin >> veb_num_in;
 VEB_Tree -> ele_in(veb_num_in);
}

cout<<"The minimum Number is:"<<endl;
cout <<VEB_Tree -> value_min()<<endl;
 //   printf("%llu\n", VEB_Tree -> value_min());
cout<<"The maximum Number is:"<<endl;
//cout <<VEB_Tree -> value_max()<<endl;
    printf("%llu\n", VEB_Tree -> value_max());

cout<<"Enter the Number for which predecessor & successor has to be found:"<<endl;
cin >>veb_num_srh;
//cout <<veb_num_srh<<endl;
cout<<"The predecessor is:"<<endl;
 
//cout <<*VEB_Tree -> predecessor(veb_num_srh)<<endl;
printf("%llu\n", (*VEB_Tree -> predecessor(veb_num_srh)));
cout<<"The successor is:"<<endl;
 printf("%llu\n", (*VEB_Tree -> successor(veb_num_srh)));


cout<<"Enter the Number to be Deleted:"<<endl; 
  cin >>veb_num_del;
//cout <<veb_num_del<<endl; 
    VEB_Tree -> ele_Del(veb_num_del);
cout<<"The new predecessor after deletion of Number is:"<<endl;
printf("%llu\n", (*VEB_Tree -> predecessor(veb_num_srh)));
cout<<"The new successor after deletion of NUmber is:"<<endl;
   printf("%llu\n", (*VEB_Tree -> successor(veb_num_srh)));

 
//cout<<"Predecessor & Successor after deletion:"<<endl;    
  //  printf("%llu\n", (*VEB_Tree -> predecessor(veb_num_srh)));
    // printf("%llu\n", (*VEB_Tree -> successor(veb_num_srh)));
    
    return 0;
}
