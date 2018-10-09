#include "../../src/BlastEngine.h"
#include "TestGame.h"

int main() {
    auto * engine = new BlastEngine();
    engine->PlayGame(*new TestGame());
}