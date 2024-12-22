#include "Graph.h"
using namespace std;

void createVertex(char newVertexID,adrVertex &v){
    v = new vertex;
    v->idVertex = newVertexID;
    v->nextVertex = nullptr;
    v->firstEdge = nullptr;
}
void initGraph(graph *G){
    G->firstVertex = nullptr;
}
void addVertex(graph *G,char newVertexID){
    adrVertex newVertex;
    createVertex(newVertexID, newVertex);

    if(G->firstVertex == nullptr){
        G->firstVertex = newVertex;
    } else {
        adrVertex temp = G->firstVertex;
        while(temp->nextVertex != nullptr){
            temp = temp->nextVertex;
        }
        temp->nextVertex = newVertex;
    }
}
void buildGraph(graph *G){
    cout << "Masukkan semua vertex (huruf), akhiri dengan #:" << endl;
    char vertexID;
    while (true) {
        cin >> vertexID;
        if (vertexID == '#') break;
        addVertex(G, vertexID);
    }
    cout << "Masukkan edge dalam format (dari ke), akhiri dengan # #:" << endl;
    char fromID, toID;
    while(true){
        cin >> fromID >> toID;
        if(fromID == '#' && toID == '#')break;

        adrVertex fromVertex = G->firstVertex;
        adrVertex toVertex = G->firstVertex;

        while (fromVertex != nullptr && fromVertex->idVertex != fromID) {
            fromVertex = fromVertex->nextVertex;
        }

        while (toVertex != nullptr && toVertex->idVertex != toID) {
            toVertex = toVertex->nextVertex;
        }

        if (fromVertex != nullptr && toVertex != nullptr) {
            addEdge(fromVertex, toVertex);
        } else {
            cout << "Vertex tidak ditemukan." << endl;
        }
    }
}
void addEdge(vertex *from, vertex *to){
    adrEdge newEdge = new edge;
    newEdge->destVertexID = to->idVertex;
    newEdge->nextEdge = from->firstEdge;
    from->firstEdge = newEdge;
}
void printGraph(graph *G){
    adrVertex tempVert = G->firstVertex;
    while(tempVert!= nullptr){
        cout << tempVert->idVertex <<":";
        adrEdge tempEdge = tempVert->firstEdge;
        while(tempEdge != nullptr){
            cout<< tempEdge->destVertexID<< " ";
            tempEdge = tempEdge->nextEdge;
        }
        cout << endl;
        tempVert = tempVert->nextVertex;
    }
}
bool cekHubungan(const graph *G, char fromID, char toID){
    adrVertex tempVert = G->firstVertex;
    while(tempVert != nullptr && tempVert->idVertex != fromID){
        tempVert = tempVert->nextVertex;
    }
    if(tempVert == nullptr) return false;

    adrEdge tempEdge = tempVert->firstEdge;
    while(tempEdge != nullptr){
        if(tempEdge->destVertexID == toID){
            return true;
        }
        tempEdge = tempEdge->nextEdge;
    }
    return false;
}
void saranFollowers(graph *G, char fromID) {
    adrVertex tempVertex = G->firstVertex;
    while (tempVertex != nullptr && tempVertex->idVertex != fromID) {
        tempVertex = tempVertex->nextVertex;
    }

    if (tempVertex == nullptr) {
        cout << "Pengguna tidak ditemukan untuk saran followers." << endl;
        return;
    }

    // Kumpulkan semua calon follower berdasarkan koneksi
    cout << "Saran Followers untuk pengguna " << fromID << ":" << endl;
    adrEdge tempEdge = tempVertex->firstEdge;
    bool hasRecommendation = false;

    // Mengumpulkan calon saran followers dari semua koneksi
    while (tempEdge != nullptr) {
        adrVertex checkUser = G->firstVertex;
        while (checkUser != nullptr && checkUser->idVertex != tempEdge->destVertexID) {
            checkUser = checkUser->nextVertex;
        }

        if (checkUser != nullptr) {
            adrEdge subEdge = checkUser->firstEdge;
            while (subEdge != nullptr) {
                // Cek apakah pengguna dariID sudah follow destVertexID atau tidak
                adrEdge checkFollow = tempVertex->firstEdge;
                bool alreadyFollowing = false;
                while (checkFollow != nullptr) {
                    if (checkFollow->destVertexID == subEdge->destVertexID) {
                        alreadyFollowing = true;
                        break;
                    }
                    checkFollow = checkFollow->nextEdge;
                }

                if (subEdge->destVertexID != fromID && !alreadyFollowing) {
                    cout << subEdge->destVertexID << " ";
                    hasRecommendation = true;
                }
                subEdge = subEdge->nextEdge;
            }
        }
        tempEdge = tempEdge->nextEdge;
    }

    if (!hasRecommendation) {
        cout << "Tidak ada rekomendasi.";
    }
    cout << endl;
}

void exportToDot(graph *G){
    cout << "digraph G {\n";
    adrVertex tempVert = G->firstVertex;
     while (tempVert != nullptr) {
        adrEdge tempEdge = tempVert->firstEdge;
        while (tempEdge != nullptr) {
            cout << "  " << tempVert->idVertex << " -> " << tempEdge->destVertexID << ";\n";
            tempEdge = tempEdge->nextEdge;
        }
        tempVert = tempVert->nextVertex;
    }
    cout << "}" << endl;
}


void deleteFirstVertex(graph *G) {
    if (G->firstVertex == nullptr) return;

    adrVertex temp = G->firstVertex;
    G->firstVertex = temp->nextVertex;

    // Free edges of the deleted vertex
    adrEdge edge = temp->firstEdge;
    while (edge != nullptr) {
        adrEdge nextEdge = edge->nextEdge;
        delete edge;
        edge = nextEdge;
    }
    delete temp;
}

void deleteLastVertex(graph *G) {
    if (G->firstVertex == nullptr) return;

    adrVertex prev = nullptr;
    adrVertex curr = G->firstVertex;

    while (curr->nextVertex != nullptr) {
        prev = curr;
        curr = curr->nextVertex;
    }

    if (prev == nullptr) {
        G->firstVertex = nullptr; // Only one vertex existed
    } else {
        prev->nextVertex = nullptr;
    }

    // Free edges of the deleted vertex
    adrEdge edge = curr->firstEdge;
    while (edge != nullptr) {
        adrEdge nextEdge = edge->nextEdge;
        delete edge;
        edge = nextEdge;
    }
    delete curr;
}

void deleteAfterVertex(graph *G, char afterID) {
    adrVertex temp = G->firstVertex;

    while (temp != nullptr && temp->idVertex != afterID) {
        temp = temp->nextVertex;
    }

    if (temp == nullptr || temp->nextVertex == nullptr) return;

    adrVertex toDelete = temp->nextVertex;
    temp->nextVertex = toDelete->nextVertex;

    // Free edges of the deleted vertex
    adrEdge edge = toDelete->firstEdge;
    while (edge != nullptr) {
        adrEdge nextEdge = edge->nextEdge;
        delete edge;
        edge = nextEdge;
    }
    delete toDelete;
}
