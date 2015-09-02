#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "poker.h"

/* converts a hand (of 5 cards) to a string representation, and stores it in the
 * provided buffer. The buffer is assumed to be large enough.
 */
void hand_to_string (hand_t hand, char *handstr) {
    char *p = handstr;
    int i;
    char *val, *suit;
    for (i=0; i<5; i++) {
        if (hand[i].value < 10) {
            *p++ = hand[i].value + '0';
        } else {
            switch(hand[i].value) {
            case 10: *p++ = 'T'; break;
            case 11: *p++ = 'J'; break;
            case 12: *p++ = 'Q'; break;
            case 13: *p++ = 'K'; break;
            case 14: *p++ = 'A'; break;
            }
        }
        switch(hand[i].suit) {
        case DIAMOND: *p++ = 'D'; break;
        case CLUB: *p++ = 'C'; break;
        case HEART: *p++ = 'H'; break;
        case SPADE: *p++ = 'S'; break;
        }
        if (i<=3) *p++ = ' ';
    }
    *p = '\0';
}

/* converts a string representation of a hand into 5 separate card structs. The
 * given array of cards is populated with the card values.
 */
void string_to_hand (const char *handstr, hand_t hand) {
  const char *s=handstr;
  int i;
  for(i=0; i<5; i++){
    switch(*s++){
    case '2': hand[i].value = 2; break;
    case '3': hand[i].value = 3; break;
    case '4': hand[i].value = 4; break;
    case '5': hand[i].value = 5; break;
    case '6': hand[i].value = 6; break;
    case '7': hand[i].value = 7; break;
    case '8': hand[i].value = 8; break;
    case '9': hand[i].value = 9; break;
    case 'T': hand[i].value = 10; break;
    case 'J': hand[i].value = 11; break;
    case 'Q': hand[i].value = 12; break;
    case 'K': hand[i].value = 13; break;
    case 'A': hand[i].value = 14; break;
    }
    switch(*s++){
    case 'D': hand[i].suit = DIAMOND; break;
    case 'C': hand[i].suit = CLUB; break;
    case 'H': hand[i].suit = HEART; break;
    case 'S': hand[i].suit= SPADE; break;
    }
    s++;
  }
}

/* sorts the hands so that the cards are in ascending order of value (two
 * lowest, ace highest */
void sort_hand (hand_t hand) {
  card_t tempHand;
  int i,j;
  for(i=1;i<5;i++){
    for(j=0;j<5-i;j++){
      if(hand[j].value>hand[j+1].value){
	tempHand=hand[j];
	hand[j]=hand[j+1];
	hand[j+1]=tempHand;
      }

    }
  }
}

int count_pairs (hand_t hand) {
  sort_hand(hand);
  int countP=0;
  int i;
  for(i=0;i<4;i++){
    if(hand[i].value==hand[i+1].value){
      countP++;
    }
  }

  return countP;
    
}

int is_onepair (hand_t hand) {
  sort_hand(hand);
  int i;
  for(i=0; i<4; i++){
    if((hand[i].value==hand[i+1].value)){ 
      return 1; 
    }    
  } 
  return 0;
}

int is_twopairs (hand_t hand) {
  sort_hand(hand);
  if((hand[0].value ==hand[1].value)&&(hand[2].value == hand[3].value)){ 
    return 1; 
  }
  if((hand[1].value ==hand[2].value) &&(hand[3].value == hand[4].value)){ 
    return 1; 
  }
  if((hand[0].value==hand[1].value)&&(hand[3].value == hand[4].value)){ 
    return 1; 
  }  
  return 0;
}

int is_threeofakind (hand_t hand) {
  sort_hand(hand);
  if((hand[0].value==hand[1].value)&&(hand[1].value==hand[2].value)){
    return 1;
  }
  else if((hand[1].value==hand[2].value)&&(hand[2].value==hand[3].value)){
    return 1;
  }
  else if((hand[2].value==hand[3].value)&&(hand[3].value==hand[4].value)){
    return 1;
  }
  return 0;
}

int is_straight (hand_t hand) {
  sort_hand(hand);
  if(((hand[0].value==hand[1].value-1)&&(hand[1].value==hand[2].value-1)&&(hand[2].value == hand[3].value-1)&&(hand[3].value == hand[4].value-1))||
     ((hand[0].value==hand[1].value-1)&&(hand[1].value==hand[2].value-1)&&(hand[2].value==hand[3].value-1)&&(hand[3].value == hand[4].value-9))){
    return 1;
  }
  return 0;
  /*int i;
  for(i=0;i<4;i++){
    if(hand[i+1].value-hand[i].value==1){
      if((i+1)==4){
	return 1;
      }
    }
    else break;
  }
  return 0;*/
}

int is_fullhouse (hand_t hand) {
  if(is_threeofakind(hand)==1){
    sort_hand(hand);
    if((hand[0].value==hand[2].value)&&(hand[3].value==hand[4].value)){
      return 1;
    }
    else if ((hand[2].value==hand[4].value)&&(hand[0].value==hand[1].value)){
      return 1;
    }
    else return 0;
  }
  else return 0;
}

int is_flush (hand_t hand) {
  int i;
  suit_t tempS=hand[0].suit;
  for(i=1;i<5;i++){
    if(hand[i].suit==tempS){
      if(i==4){
	return 1;
      }
    }
    else break;
  }
  return 0;
}

int is_straightflush (hand_t hand) {
  if((is_straight(hand)==1) && (is_flush(hand)==1)){
    return 1;
  } 
  return 0;
}

int is_fourofakind (hand_t hand) {
  sort_hand(hand);  
  if((hand[0].value ==hand[1].value)&&(hand[1].value==hand[2].value)&&(hand[2].value == hand[3].value)){ 
    return 1; 
  }
  else if((hand[1].value == hand[2].value)&&(hand[2].value==hand[3].value)&&(hand[3].value==hand[4].value)){ 
    return 1; 
  }  
  return 0;
}

int is_royalflush (hand_t hand) {
  sort_hand(hand);
  if((hand[0].value==10)&&(is_straightflush(hand))){
    return 1;
  }
  else return 0;
}

/* compares the hands based on rank -- if the ranks (and rank values) are
 * identical, compares the hands based on their highcards.
 * returns 0 if h1 > h2, 1 if h2 > h1.
 */
int compare_hands (hand_t h1, hand_t h2) {
  sort_hand(h1);
   sort_hand(h2);
   if((is_royalflush(h1)==1)&&(is_royalflush(h2)==0)){
     return 0;
   }
   else if((is_royalflush(h1)==0)&&(is_royalflush(h2)==1)){
     return 1;
   }
   else{
     if((is_straightflush(h1)==1)&&(is_straightflush(h2)==0)){
       return 0;
     }
     else if((is_straightflush(h1)==0)&&(is_straightflush(h2)==1)){
       return 1;
     }
     else if((is_straightflush(h1)==1)&&(is_straightflush(h2)==1)){
       return compare_highcards(h1,h2);
     }
     else{
       if((is_fourofakind(h1)==1)&&(is_fourofakind(h2)==0)){
	 return 0;
       }
       else if((is_fourofakind(h1)==0)&&(is_fourofakind(h2)==1)){
	 return 1;
       }
       else if((is_fourofakind(h1)==1)&&(is_fourofakind(h2)==1)){
	 return compare_highcards(h1,h2);
       }
       else{
	 if((is_fullhouse(h1)==1)&&(is_fullhouse(h2)==0)){
	     return 0;
	 }
	 else if((is_fullhouse(h1)==0)&&(is_fullhouse(h2)==1)){
	     return 1;
	 }
	 else if((is_fullhouse(h1)==1)&&(is_fullhouse(h2)==1)){
	     return compare_highcards(h1,h2);
	 }
	 else{
	    if((is_flush(h1)==1)&&(is_flush(h2)==0)){
	     return 0;
	   }
	   else if((is_flush(h1)==0)&&(is_flush(h2)==1)){
	     return 1;
	   }
	   else if((is_flush(h1)==1)&&(is_flush(h2)==1)){
	     return compare_highcards(h1,h2);
	   }
	   else{
	     if((is_straight(h1)==1)&&(is_straight(h2)==0)){
	       return 0;
	     }
	     else if((is_straight(h1)==0)&&(is_straight(h2)==1)){
	       return 1;
	     }
	     else if((is_straight(h1)==1)&&(is_straight(h2)==1)){
	       return compare_highcards(h1,h2);
	     }
	     else{
	       if((is_threeofakind(h1)==1)&&(is_threeofakind(h2)==0)){
		 return 0;
	       }
	       else if((is_threeofakind(h1)==0)&&(is_threeofakind(h2)==1)){
		 return 1;
	       }
	       else if((is_threeofakind(h1)==1)&&(is_threeofakind(h2)==1)){
		 return compare_highcards(h1,h2);
	       }
	       else{
		 if((is_twopairs(h1)==1)&&(is_twopairs(h2)==0)){
		   return 0;
		 }
		 else if((is_twopairs(h1)==0)&&(is_twopairs(h2)==1)){
		   return 1;
		 }
		 else if((is_twopairs(h1)==1)&&(is_twopairs(h2)==1)){
		   return compare_highcards(h1,h2);
		 }
		 else{
		   if((is_onepair(h1)==1)&&(is_onepair(h2)==0)){
		     return 0;
		   }
		   else if((is_onepair(h1)==0)&&(is_onepair(h2)==1)){
		     return 1;
		   }
		   else if((is_onepair(h1)==1)&&(is_onepair(h2)==1)){
		     return compare_highcards(h1,h2);
		   }
		   else{
		     return compare_highcards(h1,h2);
		   }
		 }
	       }
	     }
	   }
	 }
       } 
     }
   }
  return compare_highcards(h1, h2);
}

/* compares the hands based solely on their highcard values (ignoring rank). if
 * the highcards are a draw, compare the next set of highcards, and so forth.
 */
int compare_highcards (hand_t h1, hand_t h2) {
  sort_hand(h1);
  sort_hand(h2);
  int i;
  for(i=4;i>-1;i--){
    if(h1[i].value>h2[i].value){
      return 0;
    }
    else if(h1[i].value<h2[i].value){
      return 1;
    }
  }
}
