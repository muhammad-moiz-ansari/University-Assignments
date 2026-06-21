#include<iostream>
#include "pch.h"
//#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 10\Lab-10 Project File\23i-0523_Moiz Ansari_Q1.cpp"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 10\Lab-10 Project File\23i-0523_Moiz Ansari_Q2.cpp"

using namespace std;
//--------------1st Question--------------

TEST(BinaryTreeTest, InsertAndDisplay) {
    BinaryTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    // Displaying the tree structure
    std::cout << "Complete Binary Tree Structure:" << std::endl;
    std::cout << "     " << "1" << std::endl;
    std::cout << "    / \\" << std::endl;
    std::cout << "   " << "2" << "   " << "3" << std::endl;
    std::cout << "  / \\ / " << std::endl;
    std::cout << "  " << "4" << " " << "5" << " " << "6" << std::endl;

    testing::internal::CaptureStdout();
    tree.Display();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Inorder Traversal: 4 2 5 1 6 3 Preorder Traversal: 1 2 4 5 3 6 Postorder Traversal: 4 5 2 6 3 1 ");
}
//--------------2nd Question--------------
TEST(FindPathSum, case1) {
    // Constructing the binary tree based on the image provided
    Node* root = new Node(10);
    root->left = new Node(8);
    root->right = new Node(2);
    root->left->left = new Node(3);
    root->left->right = new Node(5);
    root->right->right = new Node(2);

    // Example target sum
    int targetSum = 14;

    // Checking if the path with the given target sum exists
    EXPECT_TRUE(hasPathSum(root, targetSum));


    ////       Test case 2       //
    //// Constructing the binary tree based on the image provided
    //Node* root2 = new Node(-2);
    //root2->right = new Node(-3);
    //
    //// Example target sum
    //int targetSum2 = -2;

    //// Checking if the path with the given target sum exists
    //EXPECT_FALSE(hasPathSum(root2, targetSum2));


    //       Test case 3       //
    // Constructing the binary tree based on the image provided
    Node* root3 = new Node(-1);
    //root3->left = new Node(9);
    root3->right = new Node(9, new Node(-6), new Node(3, NULL, new Node(-2)));

    // Example target sum
    int targetSum3 = 9;

    // Checking if the path with the given target sum exists
    EXPECT_TRUE(hasPathSum(root3, targetSum3));
}
