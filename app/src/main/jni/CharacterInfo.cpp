    struct CharacterInfo {
        char32_t index;       // 字符索引
        float advance;        // 字符的前进距离
        float minX;           // 字符的最小 X 坐标
        float minY;           // 字符的最小 Y 坐标
        float maxX;           // 字符的最大 X 坐标
        float maxY;           // 字符的最大 Y 坐标
        Vector2 uv0;          // 字符的 UV 坐标（左下角）
        Vector2 uv1;          // 字符的 UV 坐标（右上角）
        Vector2 offset;       // 字符的偏移量
        Vector2 padding;      // 字符的内边距
    };

