#include <iostream>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <typeinfo>
#include "GameObject.h"
#include "GameObjectList.h"
#include "Circulo.h"
#include "Retangulo.h"
#include <math.h>


using namespace std;
    GameObjectList::GameObjectList() {
        this->inicio = NULL;
    }


	void GameObjectList::Adicionar(GameObject *item) {
	    /*NoDaLista *novo = new NoDaLista();
        novo->prox = NULL;
        novo->valor = item; 

        NoDaLista *aux = lista;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;*/

        NoDaLista * novo = new NoDaLista();
        novo->valor = item;
        novo->prox = NULL;

        if(this->inicio == NULL){
            this->inicio = novo;
        }
        else {
            NoDaLista *atual;
            atual = this->inicio;
            while(atual->prox !=NULL){
                atual=atual->prox;
            }
            atual->prox = novo;
        }
        //std::cout << "Bala adicionada na lista com x: "<< item->posicao_x << " e y: " << item->posicao_y << std::endl;


    }

    void GameObjectList::RemoverSeq(GameObject *item) {
        NoDaLista *aux;
        if (this->inicio == NULL ) {
            cout << "Lista vazia" << endl;
        }
        else {
            aux = inicio->prox;
            delete(item);
        }
    }

    void GameObjectList::Remover(GameObject *item){
        if(this->inicio == NULL) {
            cout << "Lista vazia" << endl;
        }
        else {
            NoDaLista *old = NULL;
            NoDaLista *curr = this->inicio;
            while (curr != NULL) {
                if (curr->valor == item) {
                    if(old != NULL) {
                        old->prox = curr->prox;
                    }
                    else {
                        this->inicio = curr->prox;
                    }
                    delete(curr);
                    delete(item);
                    return;
                }
                old = curr;
                curr = curr->prox;
            }       
        }
    }

    void GameObjectList::Render(){
        NoDaLista *aux = inicio;
        while (aux != NULL){
            aux->valor->Render();
            aux = aux->prox;
        }
    }

    //void GameObjectList::Update(GameObjectList *Lista){
    void GameObjectList::Update(){
        NoDaLista *aux = inicio;
        while (aux != NULL){
            aux->valor->Update();
            if(aux->valor->Devo_Morrer()){
                this->Remover(aux->valor);
            }
            
            aux = aux->prox;
        }
    }

    void GameObjectList::Impacto(GameObjectList *Lista){
        NoDaLista *auxUm = this->inicio;
        NoDaLista *auxDois = Lista->inicio;
        while(auxUm != NULL){
            while(auxDois !=NULL){
                if(sqrt((auxDois->valor->posicao_x - auxUm->valor->posicao_x) * (auxDois->valor->posicao_x - auxUm->valor->posicao_x) + 
                        (auxDois->valor->posicao_y - auxUm->valor->posicao_y) * (auxDois->valor->posicao_y - auxUm->valor->posicao_y)) 
                        <= auxUm->valor->size + auxDois->valor->size){
                    std::cout << "Existem elementos para serem destruidos" << std::endl;
                    this->Remover(auxUm->valor);
                    Lista->Remover(auxDois->valor);
                }
                auxDois=auxDois->prox;
            }
            auxUm=auxUm->prox;
        }

    }

    int GameObjectList::MouseDown(float x, float y){
        NoDaLista *aux = inicio;
        std::cout<<"Posicao do x do clic: " << x << std::endl;
        std::cout<<"Posicao do y do clic: " << y << std::endl;    
        while (aux != NULL)
        {
            if(aux->valor->MouseDown(x,y)) {
                return 1;
                break;
            }
            aux = aux->prox;
        }
        return 0;
    }
