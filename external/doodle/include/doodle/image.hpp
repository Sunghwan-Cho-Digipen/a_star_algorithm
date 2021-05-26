/*--------------------------------------------------------------*
  Copyright (C) 2019 Rudy Castan

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `License.md' for details.
*--------------------------------------------------------------*/
#pragma once

#include <filesystem>

namespace doodle
{
    struct Color;

    /**
     * \addtogroup Image
     *  Image class to store a 2D array of colors
     *  @{
     */

    /**
     * \brief Image class to store a 2D array of RGBA colors. Also manages an image on the Graphics Card.
     *
     * The Image class is useful for creating images programmatically. It is also useful for loading and creating image
     * files
     *
     */
    class [[nodiscard]] Image
    {
    public:
        /**
         * \brief Get the maximum image size allowed.
         *
         * This maximum size is defined by the graphics driver. You can expect a value of 1024 pixels for low-end
         * graphics card, and up to 8192 pixels or more for newer hardware.
         *
         * \return Maximum size allowed for images, in pixels
         *
         * \pre Since this involves talking with the GPU a connection must already be established, so create_window()
         * must have already been called.
         */
        static int MaxImageSize() noexcept;

    public:
        /**
         * \brief Construct an empty image with a provided resolution
         *
         * \param width how wide to make the image
         * \param height how tall to make the image
         * \param smooth_it When the filter is activated, the texture appears smoother so that pixels are less
         * noticeable. However if you want the texture to look exactly the same as its source file, you should leave it
         * disabled. The smooth filter is disabled by default.
         *
         * \exception std::runtime_error if width/height is <= 0 or is too large
         *
         * \pre Since this involves talking with the GPU a connection must already be established, so create_window()
         * must have already been called.
         *
         */
        Image(int width, int height, bool smooth_it = false);
        /**
         * \brief Create an Image based off of an image file. The supported image formats are defined by the
         * Image::FileType enum.
         *
         * \param file_path path to an image file
         * \param smooth_it When the filter is activated, the texture appears smoother so that pixels are less
         * noticeable. However if you want the texture to look exactly the same as its source file, you should leave it
         * disabled. The smooth filter is disabled by default.
         *
         * \exception std::runtime_error if it cannot find the file or if it can't read it
         *
         * \pre Since this involves talking with the GPU a connection must already be established, so create_window()
         * must have already been called.
         *
         * 
         */
        explicit Image(const std::filesystem::path& file_path, bool smooth_it = false);
        /**
         * \brief Creates an empty image
         *
         * \pre Since this involves talking with the GPU a connection must already be established, so create_window()
         * must have already been called.
         */
        Image();
        /**
         * \brief Destructor
         *
         * Release all image resources
         *
         * \warning This will likely fail if the instance is in a global scope because the GPU connection will have
         * already been disconnected when the program shuts down.
         */
        ~Image();
        /**
         * \brief One cannot copy an Image object
         *
         *  Images take up a lot of memory in your application and on the GPU, so we don't want to duplicate them.
         *
         */
        Image(const Image&) = delete;
        /**
         * \brief One cannot copy an Image object
         *
         * Images take up a lot of memory in your application and on the GPU, so we don't want to duplicate them.
         *
         */
        Image& operator=(const Image&) = delete;
        /**
         * \brief Image can be moved
         *
         * Since move resources around doesn't duplicate them, it is okay to move them with r-value references.
         *
         */
        Image(Image && other) noexcept;
        /**
         * \brief Image can be moved
         *
         * Since move resources around doesn't duplicate them, it is okay to move them with r-value references.
         *
         */
        Image& operator=(Image&& other) noexcept;

        /**
         * \brief Lists all of the supported image file formats
         */
        enum class FileType
        {
            /**
             * \brief Portable Network Graphics file format
             */
            PNG,
            /**
             * \brief Bitmap file format
             */
            BMP,
            /**
             * \brief Targe file format
             */
            TGA,
            /**
             * \brief JPEG file format
             */
            JPG
        };
        /**
         * \brief Save the Image as an image file on disk.
         *
         * You should not be giving a directory file path and you will need to add the image extension yourself.
         * \param file_path file path to save the image file to.
         * \param file_type the type of the image file to create
         */
        void SaveToFile(const std::filesystem::path& file_path, FileType file_type = FileType::PNG) const;
        /**
         * \brief Return the width of the image.
         * \return width of the Image
         */
        int GetWidth() const noexcept;
        /**
         * \brief Return the height of the image.
         * \return height of the Image
         */
        int GetHeight() const noexcept;
        /**
         * \brief Return the total number of colors in the image
         * \return the total number of colors in the Image
         */
        int GetNumberOfColors() const noexcept;
        /**
         * \brief Tell whether the smooth filter is enabled or not.
         * \return True if smoothing is enabled, false if it is disabled
         */
        bool IsSmooth() const noexcept;

        /**
         * \brief struct to represent the colors of the Image.
         */
        struct color
        {
            using byte = unsigned char;
            byte red = 0, green = 0, blue = 0, alpha = 255;

            /**
             * \brief Defaults to black
             */
            color() = default;
            /**
             * \brief Can be constructed from a Color object
             * \param c Color object
             */
            color(const doodle::Color& c) noexcept;
            /**
             * \brief Can be implicitly converted to a Color object
             */
            operator doodle::Color() const noexcept;
        };

        /**
         * \brief Get a specific color from the image
         * \param index Should be 0 \f$\leq\f$ index \f$<\f$ GetNumberOfColors()
         * \return a copy of the color at that position
         * \exception std::out_of_range if index is out of range.
         *
         *
         */
        color operator[](int index) const;
        /**
         * \brief Get a specific color from the image, so that you can change the image contents.
         * Usage of this will trigger creating a new GPU texture when the Image is drawn via draw_image().
         * \param index Should be 0 \f$\leq\f$ index \f$<\f$ GetNumberOfColors()
         * \return a reference of the color at that position
         * \exception std::out_of_range if index is out of range.
         *
         *
         */
        color& operator[](int index);

        /**
         * \brief Get a specific color from the image
         * \param column Should be 0 \f$\leq\f$ column \f$<\f$ GetWidth()
         * \param row Should be 0 \f$\leq\f$ row \f$<\f$ GetHeight()
         * \return a copy of the color at that position
         * \exception std::out_of_range if column or row is out of range.
         *
         *
         */
        color operator()(int column, int row) const;
        /**
         * \brief Get a specific color from the image, so that you can change the image contents.
         * Usage of this will trigger creating a new GPU texture when the Image is drawn via draw_image().
         * \param column Should be 0 \f$\leq\f$ column \f$<\f$ GetWidth()
         * \param row Should be 0 \f$\leq\f$ row \f$<\f$ GetHeight()
         * \return a reference of the color at that position
         * \exception std::out_of_range if column or row is out of range.
         *
         *
         */
        color& operator()(int column, int row);

        /**
         * \brief Returns an iterator to the first color of the Image.
         *
         * Usage of this will trigger creating a new GPU texture when the Image is drawn via draw_image().
         *
         * Having a begin/end interface enables the Image class to be used with for range loops and the std <algorithm>
         * functions.
         *
         * \return iterator to the first element
         *
         *
         */
        color* begin();
        /**
         * \brief
         * \return
         *
         *
         */
        color* end();

        /**
         * \brief Returns a const iterator to the first color of the Image.
         *
         * Having a begin/end interface enables the Image class to be used with for range loops and the std <algorithm>
         * functions.
         *
         * \return const iterator to the first element
         *
         *
         */
        const color* begin() const;
        /**
         * \brief Returns a const iterator to the color following the last color of the Image.
         *
         * This color acts as a placeholder; attempting to access it results in undefined behavior.
         *
         * Having a begin/end interface enables the Image class to be used with for range loops and the std <algorithm>
         * functions.
         *
         * \return const iterator to a color following the last color
         *
         *
         */
        const color* end() const;

    private:
        class ImageImpl;
        std::unique_ptr<ImageImpl> impl;

    private:
        friend void draw_image(const Image& image, double x, double y) noexcept;
        friend void draw_image(const Image& image, double x, double y, double width, double height) noexcept;
        friend void draw_image(const Image& image, double x, double y, double width, double height) noexcept;
        friend void draw_image(const Image& image, double x, double y, double width, double height, int texel_x,
                               int texel_y) noexcept;
        friend void draw_image(const Image& image, double x, double y, double width, double height, int texel_x,
                               int texel_y, int texel_width, int texel_height) noexcept;
    };
    /** @} */
}
