typedef enum
{
    e_red,
    e_black,
}e_color_t;
typedef struct
{
    int key;
    e_color_t color;
}rbtree_entry_t;
typedef struct
{
    rbtree_entry_t *root;
}rbtree_t;
