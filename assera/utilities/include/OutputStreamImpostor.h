////////////////////////////////////////////////////////////////////////////////////////////////////


//  Authors: Chuck Jacobs, Ofer Dekel, Kern Handa
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <memory>
#include <ostream>

namespace assera
{
namespace utilities
{
    /// <summary> An imposter class that can stand in for a std::ostream object </summary>
    class OutputStreamImpostor
    {
    public:
        /// <summary> Types of standard output streams, that are not file streams. </summary>
        enum class StreamType
        {
            cout,
            cerr,
            null
        };

        OutputStreamImpostor();
        ~OutputStreamImpostor() = default;

        OutputStreamImpostor(const OutputStreamImpostor&) noexcept = default;
        OutputStreamImpostor& operator=(const OutputStreamImpostor&) noexcept = default;

        OutputStreamImpostor(OutputStreamImpostor&&) noexcept = default;
        OutputStreamImpostor& operator=(OutputStreamImpostor&&) noexcept = default;

        /// <summary> Constructor that creates an object that directs output to a specified stream. </summary>
        ///
        /// <param name="streamType"> Type of the stream, defaults to the null stream. </param>
        OutputStreamImpostor(StreamType streamType);

        /// <summary> Constructor that creates an object that directs output to a file</summary>
        ///
        /// <param name="filename"> A filename </param>
        OutputStreamImpostor(const std::string& filename);

        /// <summary> Constructor that creates an object that directs output to an existing stream</summary>
        ///
        /// <param name="stream"> A stream </param>
        OutputStreamImpostor(std::ostream& stream);

        /// <summary> Casting operator that returns a reference to an ostream. This allows us to use an OutputStreamImpostor
        /// in most places where an ostream would be accepted. </summary>
        ///
        /// <returns> A reference to the underlying std::ostream object </returns>
        operator std::ostream&() & noexcept { return _outputStream; }

        /// <summary> Casting operator that returns a const reference to an ostream. This allows us to use an OutputStreamImpostor
        /// in most places where a const ostream reference would be accepted. </summary>
        ///
        /// <returns> A reference to the underlying std::ostream object </returns>
        operator std::ostream const&() const& noexcept { return _outputStream; }

        /// <summary> Output operator that sends the given value to the output stream </summary>
        ///
        /// <param name="value"> The value to output </param>
        template <typename T>
        std::ostream& operator<<(T&& value);

        /// <summary> Returns the current floating-point precision setting for the stream </summary>
        std::streamsize precision() const;

        /// <summary> Sets the floating-point precision setting for the stream </summary>
        ///
        /// <returns> The previous floating-point precision setting for the stream </summary>
        std::streamsize precision(std::streamsize prec);

        /// <summary> Sets the specified format flags for the stream to on</summary>
        ///
        /// <param name="fmtfl"> The flags to set. Only flags with a `1` set are modified. </param>
        ///
        /// <returns> The previous format flags for the stream </returns>
        std::ios_base::fmtflags setf(std::ios_base::fmtflags fmtfl);

        /// <summary> Sets or clears the specified format flags for the stream, depending on a mask </summary>
        ///
        /// <param name="fmtfl"> The values to set the flags to (`0` or `1`). Only flags with a `1` in the corresponding mask bitfield are modified. </param>
        /// <param name="mask"> A bitmask indicating the flags to modify. Only flags with a `1` set in the mask are modified. </param>
        ///
        /// <returns> The previous format flags for the stream </returns>
        std::ios_base::fmtflags setf(std::ios_base::fmtflags fmtfl, std::ios_base::fmtflags mask);

    private:
        std::shared_ptr<std::ofstream> _fileStream;

        // std::reference_wrapper<T> provides convenient value semantics
        // while retaining a reference to the underlyng `std::ostream` object
        std::reference_wrapper<std::ostream> _outputStream;
    };
} // namespace utilities
} // namespace assera

#pragma region implementation

namespace assera
{
namespace utilities
{
    template <typename T>
    std::ostream& OutputStreamImpostor::operator<<(T&& value)
    {
        _outputStream.get() << value;
        return _outputStream;
    }
} // namespace utilities
} // namespace assera

#pragma endregion implementation
