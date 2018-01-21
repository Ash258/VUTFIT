# TRP

![Diagram ginatury](https://image.prntscr.com/image/w-E-b8TQTeW-tz4akxFFkw.png "Diagram ginatury")

## Zřetězení

Při **explicitním** zřetězení obsahuje prvek adresu následníka.
Při **implicitním** zřetězení je adresa následníka funkcí adresy předchůdce.

## Brentova varianta

Varianta TRP s 2 rozptylovacími funkcemi. Je vhodná, když je počet případů úspěšného vyhledávání častější než počet neúspěšného vyhledávání s následným vkládáním. (Provádí rekonfiguraci prvků v poli)

## Funkce

### Search

```c
tHTItem* htSearch(tHTable* ptrht, tKey key) {
    tHTItem* found = (*ptrht)[hashCode(key)];

    while (found && (strcmp(found->key, key) != 0)) {
        found = found->ptrnext;
    }

    return found;
}
```

### Insert

```c
void htInsert(tHTable* ptrht, tKey key, tData data) {
    if (!ptrht) return;
    tHTItem* found = htSearch(ptrht, key);

    if (found) {
        found->data = data;
    } else {
        tHTItem* new = malloc(sizeof(tHTItem));
        if (new == NULL) return;

        new->key     = key;
        new->data    = data;
        new->ptrnext = (*ptrht)[hashCode(key)]; // Next of new = first
        (*ptrht)[hashCode(key)] = new; // First = new
    }
}
```

### Delete

```c
void htDelete(tHTable* ptrht, tKey key) {
    tHTItem* prev = NULL, * found = (*ptrht)[hashCode(key)];

    while ((found) && (strcmp(found->key, key) != 0)) {
        prev  = found;
        found = found->ptrnext;
    }

    if (!found) return;
    if (!prev) {
        (*ptrht)[hashCode(key)] = found->ptrnext; // First
    } else {
        prev->ptrnext = found->ptrnext;
    }
    free(found);
}
```
