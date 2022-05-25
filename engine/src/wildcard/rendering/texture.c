#include "texture.h"

#include <stb_image.h>
#include <glad/glad.h>

#include "internal/wldc_mem.h"
#include "core/asserts.h"

texture create_texture(const char* filepath, bool8 flipped) {
    texture tex;

    wldc_zero_mem(&tex, sizeof(tex));

    glCreateTextures(GL_TEXTURE_2D, 1, &tex.gl_id);
    glBindTexture(GL_TEXTURE_2D, tex.gl_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(flipped);

    u8* data = stbi_load(filepath, &tex.width, &tex.height, &tex.number_of_channels, 0);

    GLenum internalFormat = GL_RGB;
    GLenum format = GL_RGB;

    if (tex.number_of_channels == 4) {
        internalFormat = GL_RGBA;
        format = GL_RGBA;
    }

    char msg[256];
    sprintf(msg, "Failed to load texture file at location '%s'", filepath);
    WLDC_ASSERT_MSG(data, msg);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tex.width, tex.height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return tex;
}
void bind_texture(texture* tex) {
    glBindTexture(GL_TEXTURE_2D, tex->gl_id);
}
void active_texture_slot(i32 slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
}
void unbind_texture(texture* tex) {
    glBindTexture(GL_TEXTURE_2D, 0);
}
void delete_texture(texture* tex) {
    glDeleteTextures(1, &tex->gl_id);
}