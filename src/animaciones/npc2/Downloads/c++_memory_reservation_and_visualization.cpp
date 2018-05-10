#include <iostream>
#include <cstdint>
#include <iomanip>

//====================================================================================
// Pretty print a 2-digits hexadecimal value
//====================================================================================
void printHexVal(uint16_t val) {
   std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) { 
   for(uint16_t l=0; l < lines; ++l) {
      std::cout << reinterpret_cast<uint16_t*>(p) << " ";
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
         std::cout << " ";
      }
      std::cout << "\n";
   }
}

class Arena {
public:
   Arena(std::size_t size) {
      // Reserve Memory
      m_nextplace = m_memory = new uint8_t[size]; //Se reservan 128 bytes
   }

   ~Arena() {
      delete [] m_memory;
   }

   void * allocate(std::size_t size) {
      uint8_t *p = m_nextplace;
      m_nextplace += size;
      return p;
   }

   void deallocate(void* p) {

   }

private:
   uint8_t *m_memory, *m_nextplace;
};

void *operator new(std::size_t size, Arena& A) {
   return A.allocate(size);
}

// Este no va ahacer nada, solo se llama cuando ocurre una excepcion en el constructor
void operator delete(void* p, Arena& A) {
   return A.deallocate(p);
}

//====================================================================================
// A simple CGameObject Class
//====================================================================================
class CGameObject {
public:
   CGameObject(uint16_t x, uint16_t y) 
      : m_x(x), m_y(y), m_id(ms_id++) {
      std::cout << "Creating CGameObject " << m_id 
                << " (" << m_x << ", " << m_y << ") "
                << " at ( " << this << ", " << sizeof(*this) << ")\n";
   }
   ~CGameObject() {
      std::cout << "Destroying CGameObject " << m_id << "\n";
   }


private:
   static uint32_t ms_id;
   uint32_t m_id;
   uint16_t m_x, m_y;
};

uint32_t CGameObject::ms_id = 1;

//====================================================================================
// Application Entry Point
//====================================================================================
int main() {
   CGameObject *g1, *g2;
   uint8_t* p, n_CGameObject;
   Arena myMem(128);

   std::cout << "START\n";

   g1 = new (myMem) CGameObject(1,2);
   g2 = new (myMem) CGameObject(3,7);
   
   // Print memory
   p  = reinterpret_cast<uint8_t*>(g1) - 16;
   printRawMem(p, 16, 4); 
   std::cout << "--------------\n";
   
   // Delete one object and print memory
   g2->~CGameObject();
   myMem.deallocate(g2);
   printRawMem(p, 16, 4);  
   std::cout << "--------------\n";

   // Delete the other object and print memory again
   g1->~CGameObject();
   myMem.deallocate(g1);
   printRawMem(p, 16, 4);
   
   return 0;
}