#include "Object3D.h"
#include "FactoryEngine.h"

void Object3D::loadDataFromFile(const char* fileName)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName);

    if (result) 
    {
        std::string path = utils::extractPath(fileName);
        pugi::xml_node buffersNode = doc.child("mesh").child("buffers");

        for (pugi::xml_node bufferNode = buffersNode.child("buffer");
             bufferNode;
             bufferNode = bufferNode.next_sibling("buffer"))
        {
            Mesh3D* m = new Mesh3D();
            Material* mat = FactoryEngine::getNewMaterial();
            m->setMaterial(mat);

            // Color
            if (bufferNode.child("material").child("color"))
            {
                std::vector<float> listcolor = utils::splitString<float>(bufferNode.child("material").child("color").text().as_string(), ',');
                mat->setColor(glm::vec4(listcolor[0], listcolor[1], listcolor[2], 1.0f));
            }

            // Shininess
            if (bufferNode.child("material").child("shininess"))
            {
                mat->setShininess(bufferNode.child("material").child("shininess").text().as_int());
            }

            // Texturas
            if (bufferNode.child("material").child("texture"))
            {
                std::string textureFile = path + bufferNode.child("material").child("texture").text().as_string();
                mat->setTexture(new GLTexture(textureFile));
                mat->setTexturing(true);
            }

            // Shaders
            if (bufferNode.child("material").child("vShader") && 
                bufferNode.child("material").child("fShader"))
            {
                std::string vShader = path + bufferNode.child("material").child("vShader").text().as_string();
                std::string fShader = path + bufferNode.child("material").child("fShader").text().as_string();
                mat->loadPrograms({vShader, fShader});
            }
            else 
            {
                std::string vShader = "data/default.vertex";
                std::string fShader = "data/default.fragment";
                mat->loadPrograms({ vShader, fShader });
            }

            std::vector<float> vList = utils::splitString<float>(bufferNode.child("coords").text().as_string(), ',');
            std::vector<float> tcList;
            std::vector<float> nList;

            // Coordenadas de textura
            if (mat->getTexturing())
            {
                tcList = utils::splitString<float>(bufferNode.child("texCoords").text().as_string(), ',');
            }

            // Normales
            if (bufferNode.child("normals"))
            {
                mat->setNormalMode(Material::PER_VERTEX);
                nList = utils::splitString<float>(bufferNode.child("normals").text().as_string(), ',');
            }

            // Iluminación (de momento parece que no hay un "lighting" en los archivos .msh)
            if (mat->getNormalMode() != Material::NONE)
            {
                mat->setLighting(true);
            }

            auto coord = vList.begin();
            auto texCoord = tcList.begin();
            auto normals = nList.begin();

            while (coord != vList.end())
            {
                vertex_t v;

                v.position.x = *coord++;
                v.position.y = *coord++;
                v.position.z = *coord++;
                v.position.w = 1.0f;

                if (tcList.size() > 0) 
                {
                    v.textCoord.x = *texCoord++;
                    v.textCoord.y = *texCoord++;
                }

                if (nList.size() > 0)
                {
                    v.normal.x = *normals++;
                    v.normal.y = *normals++;
                    v.normal.z = *normals++;
                    v.normal.w = 0.0f;
                }

                m->addVertex(v);
            }

            *(m->getTriangleIdxList()) = utils::splitString<unsigned int>(bufferNode.child("indices").text().as_string(), ',');

            setMesh(m);
        }
    }
    else {
        // No se ha podido cargar
        std::cout << result.description() << std::endl;
    }
}
