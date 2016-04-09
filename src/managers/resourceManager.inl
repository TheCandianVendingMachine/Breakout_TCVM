template<typename T>
T *resourceManager<T>::get(const std::string &resourceName)
    {
        auto it = m_textures.find(resourceName);
        if (it != m_textures.end())
            {
                return it->second.get();
            }

        return nullptr;
    }

template<typename T>
T *resourceManager<T>::add(const std::string &filepath, const std::string &resourceName)
    {
        T *newResource = get(resourceName);
        if (newResource)
            {
                return newResource;
            }

        newResource = new T;
        if (newResource->loadFromFile(filepath))
            {
                m_textures[resourceName] = std::make_shared<T>(*newResource);
                return m_textures[resourceName].get();
            }
            
        return nullptr;
    }