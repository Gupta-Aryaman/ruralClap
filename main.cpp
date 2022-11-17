#include<bits/stdc++.h>
#include "avl.cpp"
using namespace std;

std::ostream& bold_on(std::ostream& os)
{
    return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
    return os << "\e[0m";
}



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
    Node* searchResult = NULL;

    int choice5;

    int z = 0;

    vector<pair<pair<string, pair<Node *, Node *>>, Node*>> treesWithSelectedWorker;
   // vector<pair<Node*, Node*>>::iterator iterator_treesWithSelectedWorker;

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

    // cout << getBalance((categoriesAlongWithSubcategoriesAndWorkers[0].second)[0].second.second);


    //////////////////////////////////////////////////////////////////////////////////////////////////////
    begin:
    int choice1;
    cout <<endl<<bold_on<< "Categories" <<bold_off<<endl;
    vector<pair<string, vector<pair<string, pair<Node*, Node*>>> >>::iterator it1; int x = 0;
    for(it1 = categoriesAlongWithSubcategoriesAndWorkers.begin(); it1 < categoriesAlongWithSubcategoriesAndWorkers.end(); it1++){
        cout << x++ <<". " <<(*it1).first << endl;
    }
    cout << "Enter your Choice: ";
    cin >> choice1;

    cout <<endl<<bold_on<< "Sub-categories" <<bold_off<<endl;
    vector<pair<string, pair<Node*, Node*>>>::iterator it2; x = 0; int choice2;
    for(it2 = categoriesAlongWithSubcategoriesAndWorkers[choice1].second.begin(); it2 < categoriesAlongWithSubcategoriesAndWorkers[choice1].second.end(); it2++){
        cout << x++ <<". " <<(*it2).first << endl;
    }
    
    cout << "Enter your Choice: ";
    cin >> choice2;

    if(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second!=NULL){
        cout <<bold_on<< "Worker already selected from the category, select another category or free the worker first!" <<bold_off<< endl <<endl;
        goto switchcase;
    }

    //pair<Node*, Node*>::iterator it2; x = 0;
    // for(it2 = categoriesAlongWithSubcategoriesAndWorkers[choice].second.[choice].second.begin(); it2 < categoriesAlongWithSubcategoriesAndWorkers[choice].second.end(); it2++){
    //     cout << x++ <<". " <<(*it2).first << endl;
    // }
    cout <<endl<<bold_on<< "Available Workers" <<bold_off<<endl;
    inOrder(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first);
    cout << endl;
    cout <<endl<<bold_on<< "Non-Available Workers" <<bold_off<<endl;
    inOrder(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second);

    int choice3;
    cout << "Select a worker by typing their id: ";
    cin >> choice3;
    
    searchResult = search(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first, choice3);
    if(searchResult!=NULL){
        categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second = insert(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second, searchResult->key, searchResult->name, searchResult->phone_number);
        categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first = deleteNode(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first, choice3);
    }
    
    treesWithSelectedWorker.push_back(make_pair(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2], categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second));
    cout <<endl<<bold_on<< "Selected By You:" <<bold_off<<endl;
    inOrderForSelected(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.second);
    cout << endl;
    //inOrder(categoriesAlongWithSubcategoriesAndWorkers[choice1].second[choice2].second.first);

    switchcase:
    cout << "1. Free a worker" << endl;
    cout << "2. Show selected workers" << endl;
    cout << "3. Select another worker" <<endl;
    cout << "4. Exit" << endl;

    int choice4;
    cin >> choice4;
    cout << endl;

    switch(choice4){
        case 1:
            
            for(auto & element:treesWithSelectedWorker){
                cout << z++ <<". "<< element.second->name<< endl;
            }
            cout << "Enter the key to be deleted" << endl;
            cin >> choice5;
            cout << endl;

            insert(treesWithSelectedWorker[choice5].first.second.first, treesWithSelectedWorker[choice5].first.second.second->key, treesWithSelectedWorker[choice5].first.second.second->name, treesWithSelectedWorker[choice5].first.second.second->phone_number);
            treesWithSelectedWorker[choice5].first.second.second = NULL;
            treesWithSelectedWorker.erase(find(treesWithSelectedWorker.begin(),treesWithSelectedWorker.end(),treesWithSelectedWorker[choice5]));

            z = 0;
            for(auto & element:treesWithSelectedWorker){
                cout << z++ <<". "<< element.second->name<< endl;
            }
            goto switchcase;
        case 2:
            for(auto & element:treesWithSelectedWorker){
                cout << "Category: " << (element.first.first) << " -> " <<bold_on<< element.second->name<<bold_off << ", " << element.second->phone_number << endl;
            }
            cout << endl;
            goto switchcase;
        case 3:
            goto begin;
        case 4:
            break;
        default:
            cout << "Wrong choice\n";
            break;
    }

    return 0;
}