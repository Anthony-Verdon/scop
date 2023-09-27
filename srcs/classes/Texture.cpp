#include "Texture.hpp"
#include "Utils.hpp"

Texture::Texture()
{
}

bool Texture::textureExtension(const std::string &texturePath, const std::string &extension) const
{
    unsigned int extensionLength;
    unsigned int texturePathLength;

    extensionLength = extension.length();
    texturePathLength = texturePath.length();
    if (texturePathLength > extensionLength && texturePath.compare(texturePathLength - extensionLength, extensionLength, extension) == 0)
        return (true);
    else
        return (false);
}

void Texture::loadImage(const std::string &texturePath)
{
    std::ifstream textureFile;
    std::stringstream textureStream;
    std::string line;
    std::vector<std::string> words;
    unsigned int nbLine;
    unsigned int pixel;
    
    nbLine = 0;
    pixel = 0;
    textureFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        textureFile.open(texturePath);
        textureStream << textureFile.rdbuf();
        textureFile.close();
        while (std::getline(textureStream, line))
        {
            line = line.substr(0, line.find("#"));
            if (line.length() == 0)
                continue ;
            if (nbLine == 0 && line != "P3")
                std::cerr << "err" << std::endl;
            else if (nbLine == 1)
            {
                words = Utils::splitLine(line);
                if (words.size() != 2)
                    std::cerr << "texture err" << std::endl;
                width = std::stoi(words[0]);
                height = std::stoi(words[1]);
                data = new unsigned char[width * height * 3];
            }
            else if (nbLine == 2)
            {
                words = Utils::splitLine(line);
                if (words.size() != 1)
                    std::cerr << "texture err" << std::endl;
                valueMax = std::stoi(words[0]);
            }
            else if (nbLine > 2)
            {
                words = Utils::splitLine(line);
                for (size_t i = 0; i < words.size(); i++)
                {
                    data[pixel] = std::stoi(words[i]);
                    pixel++;
                }
            }
            nbLine++;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "error: " << e.what() << line << '\n';
    }
}

Texture::Texture(const std::string &texturePath)
{
    loadImage(texturePath);
    if (data == NULL)
    {
        std::cerr << "ERROR::TEXTURE::LOADING_FAILDED" << std::endl;
        ID = 0;
        return ;
    }
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    delete []data;
}

Texture::Texture(const Texture &copy)
{
    *this = copy;
}

Texture& Texture::operator=(const Texture &copy)
{
     if (&copy != this)
    {
        this->ID = copy.getID();
    }
    return (*this);
}

Texture::~Texture()
{
}

void Texture::initTexParameter()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

unsigned int Texture::getID() const
{
    return (ID);
}