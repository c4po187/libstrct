/*********************************************
 *                                           
 * STRING COMMON TASKS LIBRARY (libstrct)    
 *											 
 *********************************************
 *											 
 * VERSION : 1.1							 
 * AUTHOR  : Rici Underwood					 
 * DATE    : 2014							 
 * LICENSE : GNU GPL v3						 
 * EMAIL   : c4po187@gmail.com				 
 *											 
 *********************************************
 *											 
 * Please do not hesitate to report any		 
 * bugs to the specified email address		 
 * above, thank you.						 
 *											 
 *********************************************/

/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
 
 #ifndef __LIBSTRCT_HPP__
 #define __LIBSTRCT_HPP__
 
 #include <algorithm>
 #include <cctype>
 #include <cstdlib>
 #include <cstring>
 #include <ctime>
 #include <iostream>
 #include <random>
 #include <sstream>
 #include <vector>
 
 #define STR std::string
 #define STR_R std::string&
 #define CSTR_R const std::string&

 /*
  * The purpose of this library is to aid developers in manipulating strings using
  * the C++ language. Regardless of what software we are developing, we always have
  * to deal with strings.
  * There are so many stirng manipulation tasks that are a simple concept on paper,
  * but require either a complex programming solution, or solutions that seem very
  * monotonous, and that is where libstrct comes in - to break the monotony!
  * So please, enjoy the simple use of this library and I hope it aids developers.
  * Any ideas for further additions to the library are always appreciated and can be
  * conveyed to the specified email address in the header of this document.
  *
  * Happy coding ;)
  */
 
 namespace libstrct {

	 /*
	  * Internal namespace for functions not to be called by the user.
	  */
 	namespace detail {
	 
		/*
		 * Changes character to uppercase if previous character is a space.
		 */
		void transform( char &c ) {
			if ( ( * ( &c - sizeof( char ) ) ) == ' ' )
				c = toupper( c );
		}
		
		/*
		 * Returns true if specified character is a vowel
		 */
		bool isVowel( const char &c )  {
			return ( c == 'A' || c == 'a' || c == 'E' || c == 'e' || c == 'I' || c == 'i' ||
				c == 'O' || c == 'o' || c == 'U' || c == 'u' );
		}
		
	}

	/*
	 * Returns the original string, but with every word starting with a capital letter.
	 */ 
	STR first_char_to_upper( STR str ) {
		str[0] = toupper( str[0] );
		std::for_each( str.begin() + 1, str.end(), detail::transform );
			
		return str;
	}
	
	/*
	 * Returns the number of words found in the specified string.
	 */
	unsigned int word_frequency( CSTR_R str ) {
		unsigned int count = 0;
		STR word;
		std::stringstream ss( str );
		
		while ( ss >> word )
			++count;
			
		return count;
	}
	
	/*
	 * Returns the number of vowels in the specified string.
	 */
	unsigned int vowel_frequency( CSTR_R str ) {
		unsigned int count = 0;
		
		for ( auto si = str.begin(); si != str.end(); ++si ) {
			if ( detail::isVowel( *si ) )
				++count;
		}
				
		return count;
	}
	
	/*
	 * Returns the longest word found in the specified string.
	 */
	STR longest_word( CSTR_R str ) {
		STR builder = "", longest = "";
		
		for ( unsigned i = 0; i < str.size(); ++i ) {
			if ( ( str[i] >= 'A' && str[i] <= 'Z' ) ||
				 ( str[i] >= 'a' && str[i] <= 'z' ) )
				builder += str[i];
			else
				builder.clear();
				
			if ( builder.size() > longest.size() )
				longest = builder;
		}
		
		return longest;
	}
	
	/*
	 * Returns true if the specified string is a Palindrome.
	 */
	bool isPalindrome( STR str ) {
		str.erase( std::remove_if( str.begin(), str.end(), ::isspace ), str.end() );
		STR copy = str;
		std::reverse( copy.begin(), copy.end() );
		
		return ( strcmp( str.c_str(), copy.c_str() ) == 0 );
	} 
	
	/*
	 * Returns a string in the format of Hours:Minutes or Minutes:Seconds, your choice.
	 */
	STR time_to_string( const int &t ) {
		std::stringstream time_ratio;
		time_ratio << ( t / 60 ) << ':' << ( t % 60 );
		
		return time_ratio.str();
	}
	
	/*
	 * Returns a scrambled string.
	 */
	STR scramble( STR str ) {
		std::seed_seq sd( str.begin(), str.end() );
		std::default_random_engine gen;

		for ( int i = str.size() - 1; i > 0; --i ) {
			gen.seed( sd );
			std::uniform_int_distribution<int> dist( 0, i );
			std::swap( str[i], str[dist( gen )] );
		}

		return str;
	}
	
	/*
	 * Returns the whole specified string, reversed.
	 */
	STR reverse_all( STR str ) {
		std::reverse( str.begin(), str.end() );

		return str;
	}

	/*
	 * Returns the portion of the string before the specified delimiter.
	 */
	STR slice_before( STR str, CSTR_R delimiter ) {
		std::size_t pos = str.find( delimiter );
		return str.substr( 0, pos );
	} 
	
	/*
	 * Returns the portion of the string after the delimiter.
	 */
	STR slice_after( STR str, CSTR_R delimiter ) {
		std::size_t pos = str.find( delimiter );
		return str.substr( ( pos + delimiter.size() ) );
	}
	
	/*
	 * Returns a vector of strings from the specified string, which has
	 * been sliced at each position where the delimiter appears.
	 */
	std::vector<STR> distribute( STR str, CSTR_R delimiter ) {
		std::vector<STR> slices;
		std::size_t pos = 0;

		while ( ( pos = str.find( delimiter ) ) != STR::npos ) {
			slices.push_back( str.substr( 0, pos ) );
			str.erase( 0, ( pos + delimiter.length() ) );
		}

		return slices;
	}
	
	/*
	 * Returns a string that Spoonerism has been performed on.
	 * A string is spoonerized by swapping the beginning of the first word in
	 * the string with the beginning of the second word.
	 * <param_name = "first_len"> : Represents the number of characters from
	 * the first word to swap.
	 * <param_name = "second_len"> : Represents the number of characters from
	 * the second word to swap.
	 * If the word frequency of the string, along with first_len and second_len
	 * exceed 2, then the original string is returned.
	 */
	STR spoonerize( STR str, const int &first_len, const int &second_len ) {
		if ( word_frequency( str ) > 2 ||
			( ( first_len < 1 || first_len > 2 ) || 
			( second_len < 1 || second_len > 2 ) ) ) 
			return str;
		
		std::stringstream ss;
		std::size_t space_pos = str.find( ' ' );

		if ( first_len == 1 && second_len == 1 ) {
			std::swap( str[0], str[( space_pos + 1 )] );
			return str;
		} else if ( first_len == 2 && second_len == 1 ) {
			ss << str[( space_pos + 1 )] << str.substr( 2, ( space_pos - 1 ) ) <<
				str.substr( 0, 2 ) << str.substr( ( space_pos + 2 ), ( str.size() - 1 ) );
		} else if ( first_len == 1 && second_len == 2 ) {
			ss << str.substr( ( space_pos + 1 ), 2 ) << str.substr( 1, space_pos ) <<
				str[0] << str.substr( ( space_pos + 3 ), ( str.size() - 1 ) );
		} else if ( first_len == 2 && second_len == 2 ) { 
			ss << str.substr( ( space_pos + 1 ), 2 ) << str.substr( 2, space_pos - 1 ) <<
				str.substr( 0, 2 ) << str.substr( ( space_pos + 3 ), ( str.size() - 1 ) );
		}

		str = ss.str();
		return str;
	}
	
 }
 
 #endif