#include "deck.h"
#include <stdlib.h>

/**
 * card_cmp - Compare two cards
 * @card1: Pointer to the first card
 * @card2: Pointer to the second card
 * Return: Integer less than, equal to, or greater than zero if
 * card1 is found, respectively, to be less than,
 * to match, or be greater than card2.
 */
int card_cmp(const void *card1, const void *card2)
{
const card_t *c1 = (*(const deck_node_t **)card1)->card;
const card_t *c2 = (*(const deck_node_t **)card2)->card;

int value_cmp = strcmp(c1->value, c2->value);
if (value_cmp != 0)
return (value_cmp);

return (c1->kind - c2->kind);
}

/**
 * sort_deck - Sort a deck of cards
 * @deck: Double pointer to the deck of cards
 */
void sort_deck(deck_node_t **deck)
{
size_t len = 0;
deck_node_t *current = *deck;

while (current != NULL)
{
len++;
current = current->next;
}

deck_node_t **array = malloc(len * sizeof(*array));
if (!array)
return (0);

current = *deck;
for (size_t i = 0; i < len; i++)
{
array[i] = current;
current = current->next;
}

qsort(array, len, sizeof(*array), card_cmp);

for (size_t i = 0; i < len; i++)
{
array[i]->prev = (i == 0) ? NULL : array[i - 1];
array[i]->next = (i == len - 1) ? NULL : array[i + 1];
}

*deck = array[0];

free(array);
}
