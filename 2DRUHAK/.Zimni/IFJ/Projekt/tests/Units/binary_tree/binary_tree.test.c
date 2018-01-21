#include <criterion/criterion.h>
#include "../../../src/binarytree/binary_tree.external.c"
#include "../../../src/binarytree/tree.binary_tree.c"

int compareNodes(TreeNodeRef node1, TreeNodeRef node2) { return strcmp(node1->key, node2->key); }

void nodeDes(TreeEntry data) { (void) data; }

BinaryTree tree;

void setup(void) {
    BT_init(&tree, compareNodes, nodeDes);
}

TestSuite(BT_Init, .init = setup);
TestSuite(BT_Insert, .init = setup);

Test(BT_Init, Empty) {
    cr_assert_null(tree.root,);
    cr_assert_not_null(tree.destructor,);
    cr_assert_not_null(tree.comparator,);
    cr_assert_not_null(tree.comparator,);
}

Test(BT_Insert, Root) {
    String first = "First";
    String one   = "1";
    BT_insert(&tree, first, one);

    cr_assert_eq(tree.root->key, first,);
    cr_assert_eq(tree.root->data, one,);
    cr_assert_null(tree.root->left,);
    cr_assert_null(tree.root->right,);
}

Test(BT_Insert, Left) {
    String left = "Left";
    String zero = "0";
    BT_insert(&tree, "Root", "1");
    BT_insert(&tree, left, zero);

    cr_assert_not_null(tree.root->left,);
    cr_assert_null(tree.root->right,);
    cr_assert_eq(tree.root->left->key, left,);
    cr_assert_eq(tree.root->left->data, zero,);
    cr_assert_null(tree.root->left->left,);
    cr_assert_null(tree.root->left->right,);
}

void setupRep(void) {
    setup();
    BT_insert(&tree, "Root", "1");
    BT_insert(&tree, "Left", "0");
    BT_insert(&tree, "RootRight", "2");
}

Test(BT_Insert, Both, .init = setupRep) {
    cr_assert_not_null(tree.root->right,);
    cr_assert_eq(tree.root->right->key, "RootRight",);
    cr_assert_eq(tree.root->right->data, "2",);
}

Test(BT_Insert, ReplaceData, .init = setupRep) {
    BT_insert(&tree, "Root", "258");
    BT_insert(&tree, "Left", "1");
    BT_insert(&tree, "RootRight", "3");

    cr_assert_eq(tree.root->key, "Root",);
    cr_assert_eq(tree.root->data, "258",);
    cr_assert_eq(tree.root->left->key, "Left",);
    cr_assert_eq(tree.root->left->data, "1",);
    cr_assert_eq(tree.root->right->key, "RootRight",);
    cr_assert_eq(tree.root->right->data, "3",);
}

/** http://prntscr.com/h8xl43 */
void setupComplex(void) {
    setup();
    BT_insert(&tree, "RootAAAA", "0");
    BT_insert(&tree, "AAAA", "-1");
    BT_insert(&tree, "AAA", "-2");
    BT_insert(&tree, "AA", "-3");
    BT_insert(&tree, "What", "1");
    BT_insert(&tree, "Wha", "2");
    BT_insert(&tree, "Wh", "3");
    BT_insert(&tree, "Whas", "4");
    BT_insert(&tree, "W", "5");
    BT_insert(&tree, "V", "6");
}

Test(BT_Insert, Complex, .init = setupComplex) {
    TreeNodeRef node = tree.root->right->left;
    cr_assert_eq(node->right->data, BT_search(&tree, "Whas"),);

    node = tree.root->left;
    cr_assert_eq(node->data, BT_search(&tree, "AAAA"),);
    cr_assert_eq(node->left->data, BT_search(&tree, "AAA"),);
    cr_assert_eq(node->left->left->data, BT_search(&tree, "AA"),);
}

Test(BT_Search, Search, .init = setupComplex) {
    cr_assert_str_eq(BT_search(&tree, "Wh"), "3",);
    cr_assert_null(BT_search(&tree, "Foo"),);
}

Test(BT_Delete, Easy, .init = setup) {
    BT_insert(&tree, "Root", "5");
    cr_assert_eq(BT_delete(&tree, "Root").data, "5",);
    cr_assert_null(BT_search(&tree, "Root"),);
}

Test(BT_Dispose, Empty, .init = setup) {
    BT_dispose(&tree, true);
    cr_assert_null(tree.root,);
    cr_assert_eq(tree.destructor, &nodeDes,);
    cr_assert_eq(tree.comparator, &compareNodes,);
}

Test(BT_Dispose, Complex, .init = setupComplex) {
    BT_dispose(&tree, true);
    cr_assert_null(tree.root,);
    cr_assert_eq(tree.destructor, &nodeDes,);
    cr_assert_eq(tree.comparator, &compareNodes,);
}
