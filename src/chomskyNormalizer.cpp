#include "../header/grammar.h"
#include "../header/chomskyNormalizer.h"
#include <string>

using namespace std;

ChomskyNormalizer::ChomskyNormalizer(const Grammar& g) {
  this->grammar = g;
}

Grammar ChomskyNormalizer::removeRecursionAtBeginning(){
  Grammar g = this->grammar.clone();
  string S = g.getStartSymbol();
  set<vector<string>> productionsS = g.getProductions(S);
  
  for(auto& prod : productionsS){
      for(auto& symbol : prod){
        if(symbol == S){
          g.setStartSymbol("S'");
          g.addProduction("S'", {"S"});
          break; 
        }
      }
  }

  return g;
}

set<string> ChomskyNormalizer::findVoidableVariables(){
  Grammar g = this->grammar.clone();
  for (auto v : g.getVariables()) {
    cout << "VAR = " << v << endl;
  }
  set<string> voidableVariables;
  for(string variable : g.getVariables()){
    cout << variable[0] << endl;
    for(vector<string> production : g.getProductions(variable)){
      if(production.size() == 1){
        if(production[0] == "&"){
          voidableVariables.insert(variable);
          break;
        }
      }
    }
  }
  for(string v : voidableVariables){
    std::cout << v << " ";
  }
  cout<<endl;

  return voidableVariables;
}

Grammar ChomskyNormalizer::removeLambdaProductions(){
  Grammar g = this->grammar.clone();
  cout << "Inicio" << endl;

  set<string> voidableVariables = findVoidableVariables();
  set<string> variables = g.getVariables();

  for(string A : g.getVariables()){
    cout << "\n\nVariavel analisada:" << A << endl;
    set<vector<string>> productionsA = g.getProductions(A);

    for(const vector<string>& rhs : productionsA){
      cout << "Producao " << A << " --> ";
      for(string s : rhs){
         cout << s << " ";
      }
      cout << endl;
      vector<int> nullablePositions;

      for(int i = 0; i < (int)rhs.size(); i++){
        cout << ">>> Componente da producao " << rhs[i] << endl;
        if(voidableVariables.count(rhs[i])){ //o simbolo rhs[i] eh anulavel?
          cout << ">>>> Essa variavel eh anulavel! --> " << rhs[i] << endl;
          nullablePositions.push_back(i);
        }
      }
      if(nullablePositions.size() > 0){
        cout << "\nPosicoes anulaveis da producao: " << endl;
      }
      for(int pos : nullablePositions){
        cout << pos << endl;
      }


      if(nullablePositions.empty()){
        continue;
      }

    }
    
  }

  return g;
}