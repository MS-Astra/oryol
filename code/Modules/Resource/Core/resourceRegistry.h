#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::resourceRegistry
    @ingroup _priv
    @brief map resource locators to resource ids for resource sharing
*/
#include "Resource/Id.h"
#include "Resource/Locator.h"
#include "Resource/ResourceLabel.h"
#include "Core/Containers/Array.h"
#include "Core/Containers/Map.h"

namespace Oryol {
namespace _priv {
    
class resourceRegistry {
public:
    /// constructor
    resourceRegistry();
    /// destructor
    ~resourceRegistry();
    
    /// setup the registry with an estimated number of entries
    void Setup(int32 reserveSize);
    /// discard the registry
    void Discard();
    /// return true if the registry has been setup
    bool IsValid() const;
    
    /// add a new resource id to the registry
    void Add(const Locator& loc, Id id, ResourceLabel label);
    /// lookup resource Id by locator
    Id Lookup(const Locator& loc) const;
    /// remove all resource matching label from registry, returns removed Ids
    Array<Id> Remove(ResourceLabel label);
    
    /// check if resource is in registry
    bool Contains(Id id) const;
    /// (debug) get the locator of a resource (fail hard if resource doesn't exist)
    const Locator& GetLocator(Id id) const;
    /// (debug) get the resource label of a resource (fail hard if resource doesn't exist)
    ResourceLabel GetLabel(Id id) const;
    
    /// (debug) get number of resources in the registry
    int32 GetNumResources() const;
    /// (debug) get resource id by index
    Id GetIdByIndex(int32 index) const;
    
private:
    #if ORYOL_DEBUG
    /// validate integrity of internal data structures
    bool checkIntegrity() const;
    #endif
    
    struct Entry {
        Entry(const Locator& loc_, Id id_, ResourceLabel label_) :
            locator(loc_),
            id(id_),
            label(label_) { };
        
        Locator locator;
        Id id;
        ResourceLabel label;
    };
    
    /// find an entry by locator
    const Entry* findEntryByLocator(const Locator& loc) const;
    /// find an entry by id
    const Entry* findEntryById(Id id) const;
    
    bool isValid;
    Array<Entry> entries;
    Map<Locator, int32> locatorIndexMap;
    Map<Id, int32> idIndexMap;
};
} // namespace _priv
} // namespace Oryol
