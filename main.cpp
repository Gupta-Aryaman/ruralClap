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
    vector<pair<string, vector<pair<string, pair<Node*, Node*>>> >> categoriesAlongWithSubcategoriesAndWorkers;
    
    while (file_input) {
 
        // Read a Line from file input
        file_input >> line;
        
        numberOfCategories = stoi(line);
        //cout << numberOfCategories << endl;
        
        //vector<pair<string, vector< pair<string, int> >>>;
        

        for(int i = 1; i <= numberOfCategories; i++){
            file_input >> nameOfCategory;
            categories.push_back(nameOfCategory);
            file_input >> line;
            
            numberOfSubcategories = stoi(line);
            // cout << numberOfSubcategories << endl;
            vector<pair<string, pair<Node*, Node*>>> temp_subcategoriesAndWorkers;

            vector<Node*> roots(1000, NULL);   //usable indices only 24 ie half of 50

            for(int j = 0; j < numberOfSubcategories; j++){
                file_input >> nameOfSubcategory;
                file_input >> line;
                // cout << line << endl;
                numberOfWorkersInACategory = stoi(line);
                vector<pair<Node*, Node*>> temp_workers;

                for(int k = 0; k < numberOfWorkersInACategory; k++){
                    file_input >> nameOfWorker;
                    file_input >> phoneNumber;
                    roots[j] = insert(roots[j], k, nameOfWorker, phoneNumber);
                    //inOrder(roots[k]); cout << endl;
                    // cout << phoneNumber << endl;
                    //temp_workers.push_back(make_pair(nameOfWorker, phoneNumber));
                }

                //temp_workers.resize(numberOfWorkersInACategory);
                temp_subcategoriesAndWorkers.push_back(make_pair(nameOfSubcategory, make_pair(roots[j], roots[50-j-1])));
            }
            //temp_subcategoriesAndWorkers.resize(numberOfSubcategories);
            categoriesAlongWithSubcategoriesAndWorkers.push_back(make_pair(nameOfCategory,temp_subcategoriesAndWorkers ));
        }
        //categoriesAlongWithSubcategoriesAndWorkers.resize(numberOfCategories);
        break;
        
        //cout << line << endl;
    }
    
    // Close the File
    file_input.close();

    // cout << (categoriesAlongWithSubcategoriesAndWorkers.size())<< endl;
    vector<pair<string, vector<pair<string, pair<Node*, Node*>>> >>::iterator it;
    // cout << numberOfCategories << endl;
    for(it = categoriesAlongWithSubcategoriesAndWorkers.begin(); it < categoriesAlongWithSubcategoriesAndWorkers.end(); it++){
        cout << 1 << endl;
    }

    cout << getBalance((categoriesAlongWithSubcategoriesAndWorkers[0].second)[0].second.first);
    
    return 0;
}