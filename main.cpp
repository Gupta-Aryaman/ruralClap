#include<bits/stdc++.h>
#include "avl.cpp"
using namespace std;


int main(){
    // freopen("input.txt", "r", stdin);       //take input from input.txt file
    // freopen("output.txt", "w", stdout);     //write output in output.txt file
    //vector<pair<string,pair<Node*, Node*>>> subcategory;
    //vector< pair<string, vector<pair<string,pair<Node*, Node*>>> >> category;

    
    ifstream file_input;
    string line;
    file_input.open("input.txt");

    int numberOfCategories;
    string nameOfCategory;
    int numberOfSubcategories;
    string nameOfSubcategory;
    int numberOfWorkersInACategory;
    string nameOfWorker;
    string phoneNumber;

    vector<string> categories;
    vector<pair<string, vector<pair<string, vector<pair<string, string>>>> >> categoriesAlongWithSubcategoriesAndWorkers;
    
    while (file_input) {
 
        // Read a Line from file input
        file_input >> line;
        
        numberOfCategories = stoi(line);
        cout << numberOfCategories << endl;
        
        //vector<pair<string, vector< pair<string, int> >>>;
        

        for(int i = 1; i <= numberOfCategories; i++){
            file_input >> nameOfCategory;
            categories.push_back(nameOfCategory);
            file_input >> line;
            
            numberOfSubcategories = stoi(line);
            // cout << numberOfSubcategories << endl;
            vector<pair<string, vector<pair<string, string>>>> temp_subcategoriesAndWorkers;
            for(int j = 1; j <= numberOfSubcategories; j++){
                file_input >> nameOfSubcategory;
                file_input >> line;
                // cout << line << endl;
                numberOfWorkersInACategory = stoi(line);
                vector<pair<string, string>> temp_workers;
                for(int k = 1; k <= numberOfWorkersInACategory; k++){
                    file_input >> nameOfWorker;
                    file_input >> phoneNumber;
                    // cout << phoneNumber << endl;
                    temp_workers.push_back(make_pair(nameOfWorker, phoneNumber));
                }
                temp_workers.resize(numberOfWorkersInACategory);
                temp_subcategoriesAndWorkers.push_back(make_pair(nameOfSubcategory, temp_workers));
            }
            temp_subcategoriesAndWorkers.resize(numberOfSubcategories);
            categoriesAlongWithSubcategoriesAndWorkers.push_back(make_pair(nameOfCategory,temp_subcategoriesAndWorkers ));
        }
        categoriesAlongWithSubcategoriesAndWorkers.resize(numberOfCategories);

        
        //cout << line << endl;
    }
 
    // Close the File
    file_input.close();
    // cout << (categoriesAlongWithSubcategoriesAndWorkers.size())<< endl;
    vector<pair<string, vector<pair<string, vector<pair<string, string>>>> >>::iterator it;
    // cout << numberOfCategories << endl;
    // for(it = categoriesAlongWithSubcategoriesAndWorkers.begin(); it < categoriesAlongWithSubcategoriesAndWorkers.end(); it++){
    //     cout << 1 << endl;
    // }
    // cout << (categoriesAlongWithSubcategoriesAndWorkers[1].second)[].second.size()<< endl;

    // Node *roots = new Node[n];  //for reference - Genes *genes=new Genes[10];
    
    // /* Constructing tree given in
    // the above figure */
    // root = insert(root, 10);
    // root = insert(root, 20);
    // root = insert(root, 30);
    // root = insert(root, 40);
    // root = insert(root, 50);
    // root = insert(root, 25);

    // inOrder(root);
    
    return 0;
}