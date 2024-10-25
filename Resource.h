#ifndef RESOURCE_H
#define RESOURCE_H

class Resource {
public:
    virtual void use() = 0;  // Abstract method for using resources
};

class Food : public Resource {
public:
    void use() override;  // Implementation for eating food
};

class Water : public Resource {
public:
    void use() override;  // Implementation for drinking water
};

class Wood : public Resource {
public:
    void use() override;  // Implementation for using wood in building
};

#endif
