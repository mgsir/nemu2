#include "watchpoint.h"
#include "expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
static int cnt = 0;

void init_wp_pool() {
    int i;
    for (i = 0; i < NR_WP; i ++) {
        wp_pool[i].NO = i;
        wp_pool[i].next = &wp_pool[i + 1];
        wp_pool[i].info = -1;
    }
    wp_pool[NR_WP - 1].next = NULL;
    head = NULL;
    free_ = &wp_pool[0];
}

/* TODO: Implement the functionality of watchpoint */
void free_wp(WP *wp, WP *head)
{
    /* delete wp from head */
    if(wp == head){
        head = head->next;
    }else{
        WP * tempHead = head;
        while(tempHead->next != wp){tempHead = tempHead->next;}
        tempHead->next = tempHead->next->next;
    }

    /* insert wp to free_ */
    WP * tempFree = free_;
    while(tempFree)
    {
        if(tempFree->next == NULL) // last one
        {
            tempFree->next = wp;
            break;
        }
        if(wp->NO > tempFree->NO  && wp->NO < tempFree->next->NO)
        {
            wp->next = tempFree->next;
            tempFree->next = wp;
            break;
        }
        tempFree = tempFree->next;
    }
}

WP* new_wp()
{
    assert(free_ != NULL);
    //int temp_cnt = cnt - 1;
    WP *removed_head = head;
    /*
    if(free_->next == NULL)
    {
        WP *temp = free_;
        int temp_cnt = NR_WP - cnt-1;
        for(int i = 0; i < temp_cnt; ++i)
        {
            temp->next = &wp_pool[i];
            temp = temp->next;
        }
        printf("1239");
    }
    */

    //if(free_->next != NULL) printf("123\n");
    if(cnt == 0) {
        if(free_->next != NULL) printf("123\n");
        head = &wp_pool[0]; 
        head->next = NULL;
        if(free_->next != NULL) printf("123\n");
    }
    else{
        while(removed_head->next){removed_head = removed_head->next;}
        removed_head->next = &wp_pool[cnt];
        removed_head->next->next = NULL;
    }


    if(cnt == NR_WP) {
        free_ = NULL;
    }else{
    if(free_->next != NULL) printf("123\n");
        free_ = free_->next;
    }
    removed_head = head;
    ++cnt;
    return removed_head;
}

