#include "Common.h"

using namespace std;


class Shape : public IShape {
private:
    virtual bool IsPointInShape(Point) const = 0;

    shared_ptr<ITexture> texture_;
    Point position_ = {};
    Size size_ = {};

    bool IsPointInSize(Point p, Size s) const {
        return p.x >= 0 && p.y >= 0 && p.x < s.width && p.y < s.height;
    }

    Size GetImageSize(const Image& image) const {
        if (image.empty()) {
            return {0, 0};
        } else {
            int width = static_cast<int>(image[0].size()); // length of first string - x
            int height = static_cast<int>(image.size()); // vector length - y
            return {width, height};
        }
    }
public:
    void SetPosition(Point position) override { position_ = position; }
    Point GetPosition() const override { return position_; }

    void SetSize(Size size) override { size_ = size; }
    Size GetSize() const override { return size_; }

    void SetTexture(shared_ptr<ITexture> texture) override {
        texture_ = move(texture);
    }
    ITexture* GetTexture() const override { return texture_.get(); }

    void Draw(Image& image) const override {
        Point p;
        Point p_image;
        char pixel;
        auto image_size = GetImageSize(image);
        for (p.y = 0; p.y < size_.height; ++p.y) {
            for (p.x = 0; p.x < size_.width; ++p.x) {
                if (IsPointInShape(p)) {
                    pixel = '.';
                    if (texture_ && IsPointInSize(p, texture_->GetSize())) {
                        pixel = texture_->GetImage()[p.y][p.x];
                    }
                    p_image = {position_.x + p.x, position_.y + p.y};
                    if (IsPointInSize(p_image, image_size)) {
                        image[p_image.y][p_image.x] = pixel;
                    }
                }
            }
        }
    }
};

class Rectangle : public Shape {
public:
    unique_ptr<IShape> Clone() const override {
        return make_unique<Rectangle>(*this);
    }

private:
    bool IsPointInShape(Point) const override { return true; } // Rectangle is full shape
};

class Ellipse : public Shape {
public:
    unique_ptr<IShape> Clone() const override {
        return make_unique<Ellipse>(*this);
    }

private:
    bool IsPointInShape(Point p) const override {
        return IsPointInEllipse(p, GetSize());
    }
};

unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type) {
        case ShapeType::Rectangle:
            return make_unique<Rectangle>();
        case ShapeType::Ellipse:
            return make_unique<Ellipse>();
    }
    return nullptr;
}
