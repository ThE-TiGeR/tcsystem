#include "TCFactory.h"
#include "TCString.h"
#include "TCOutput.h"
#include "TCUtil.h"

#include "TCDebugNew.h"

namespace tc
{
   namespace math_sheet
   {
      class MathCalculation
      {
      public:
         virtual std::string GetNextCalculationString(const std::string& sep) = 0;

         virtual ~MathCalculation() {}
      };

      class Addition: public MathCalculation
      {
      public:
         Addition(uint32_t max_value)
            :m_max_value(max_value),
            m_rng(factory::Create69069Rng())
         {
         }

         virtual std::string GetNextCalculationString(const std::string& sep)
         {
            uint32_t value1 = m_rng->GetRandomNumber(1, m_max_value);
            uint32_t value2 = m_rng->GetRandomNumber(1, m_max_value - value1);

            return string::ToString(value1) + 
               sep + "+" + sep + string::ToString(value2);
         }

      private:
         uint32_t m_max_value;
         RngPtr m_rng;
      };

      class Subtraction: public MathCalculation
      {
      public:
         Subtraction(uint32_t max_value)
            :m_max_value(max_value),
            m_rng(factory::Create69069Rng())
         {
         }

         virtual std::string GetNextCalculationString(const std::string& sep)
         {
            uint32_t value1 = m_rng->GetRandomNumber(1, m_max_value-1);
            uint32_t value2 = m_rng->GetRandomNumber(1, value1);

            return string::ToString(value1) + 
               sep + "-" + sep + string::ToString(value2);
         }

      private:
         uint32_t m_max_value;
         RngPtr m_rng;
      };

      class Multiplication: public MathCalculation
      {
      public:
         Multiplication(uint32_t max_multiplayer1, uint32_t max_multiplayer2)
            :m_max_multiplayer1(max_multiplayer1),
            m_max_multiplayer2(max_multiplayer2),
            m_rng(factory::Create69069Rng())
         {
         }

         virtual std::string GetNextCalculationString(const std::string& sep)
         {
            uint32_t value1 = m_rng->GetRandomNumber(1, m_max_multiplayer1);
            uint32_t value2 = m_rng->GetRandomNumber(1, m_max_multiplayer2);

            return string::ToString(value1) +
               sep + "*" + sep + string::ToString(value2);
         }

      private:
         uint32_t m_max_multiplayer1;
         uint32_t m_max_multiplayer2;
         RngPtr m_rng;
      };

      class Multiplication10: public Multiplication
      {
      public:
         Multiplication10(uint32_t max_multiplayer)
            :Multiplication(max_multiplayer, max_multiplayer)
         {
         }

         virtual std::string GetNextCalculationString(const std::string& sep)
         {
            return Multiplication::GetNextCalculationString(sep) + "0";
         }
      };

      class Division: public MathCalculation
      {
      public:
         Division(uint32_t max_divider1, uint32_t max_divider2)
            :m_max_divider1(max_divider1),
            m_max_divider2(max_divider2),
            m_rng(factory::Create69069Rng())
         {
         }

         virtual std::string GetNextCalculationString(const std::string& sep)
         {
            uint32_t value1 = m_rng->GetRandomNumber(1, m_max_divider1);
            uint32_t value2 = m_rng->GetRandomNumber(1, m_max_divider2);

            return string::ToString(value1 * value2) + 
               sep + ":" + sep + string::ToString(value2);
         }

      private:
         uint32_t m_max_divider1;
         uint32_t m_max_divider2;
         RngPtr m_rng;
      };

      class Settings
      {
      public:
         Settings()
            :m_file_name("C:\\math_sheet.csv"),
            m_num_calculations(200),
            m_create_addition(true),
            m_create_subtraction(true),
            m_create_multiplication(true),
            m_create_multiplication10(true),
            m_create_division(true),
            m_max_add_sub_value(100),
            m_max_mult_div_value1(500),
            m_max_mult_div_value2(10)
         {
         }

      public:
         std::string m_file_name;
         uint32_t m_num_calculations;
         bool m_create_addition;
         bool m_create_subtraction;
         bool m_create_multiplication;
         bool m_create_multiplication10;
         bool m_create_division;

         uint32_t m_max_add_sub_value;
         uint32_t m_max_mult_div_value1;
         uint32_t m_max_mult_div_value2;
      };

      void DisplayUsage()
      {
         const char* message =
            "  -f, --file              name of the output file\n"
            "  -n, --num_calculations  number of calculations\n"
            "     Calculation types(optional):\n"
            "     -a, --addition         enable addition\n"
            "     -s, --subtraction      enable subtraction\n"
            "     -m, --multiplication   enable multiplication\n"
            "     --multiplication10     enable multiplication of 10\n"
            "     -d, --division         enable division\n"
            "\n"
            "  Configuration values(optional):\n"
            "     --max_add_sub_value    maximum value of an addition or subtraction\n"
            "     --max_mult_div_value1  maximum first multiplication value\n"
            "     --max_mult_div_value2  maximum second multiplication value\n";

            std::printf("math_sheet Usage:\n%s\n", message);
      }

      bool ParseCommandLine(int narg, const char** argv, Settings& settings)
      {
         if (narg < 3 || ((narg-1) % 2) != 0)
         {
            TCERRORS("math_sheet", "Wrong command line arguments");
            DisplayUsage();
            return false;
         }

         for (int i=1; i<narg-1; i++)
         {
            std::string current_arg(argv[i]);
            if (current_arg == "-f" || current_arg == "--file")
            {
               settings.m_file_name = argv[++i];
            }
            else if (current_arg == "-a" || current_arg == "--addition")
            {
               settings.m_create_addition = string::ToBool(argv[++i]);
            }
            else if (current_arg == "-s" || current_arg == "--subtraction")
            {
               settings.m_create_subtraction = string::ToBool(argv[++i]);
            }
            else if (current_arg == "-m" || current_arg == "--multiplication")
            {
               settings.m_create_multiplication = string::ToBool(argv[++i]);
            }
            else if (current_arg == "-d" || current_arg == "--division")
            {
               settings.m_create_division = string::ToBool(argv[++i]);
            }
            else if (current_arg == "-n" || current_arg == "--num_calculations")
            {
               settings.m_num_calculations = string::ToUint32(argv[++i]);
            }
            else if (current_arg == "--max_add_sub_value")
            {
               settings.m_max_add_sub_value = string::ToUint32(argv[++i]);
            }
            else if (current_arg == "--max_mult_div_value1")
            {
               settings.m_max_mult_div_value1 = string::ToUint32(argv[++i]);
            }
            else if (current_arg == "--max_mult_div_value2")
            {
               settings.m_max_mult_div_value2 = string::ToUint32(argv[++i]);
            }
            else
            {
               TCERRORS("math_sheet", "Wrong command line arguments");
               DisplayUsage();
               return false;
            }
         }

         return true;
      }

      void Create(const Settings& settings)
      {
         StreamPtr out = factory::CreateFileStream(settings.m_file_name,
            Stream::Direction::WRITE, factory::CreateAsciiCodec());
         RngPtr rng = factory::Create69069Rng();

         std::vector< SharedPtr<MathCalculation> > calculations;
         if (settings.m_create_division)
         {
            calculations.push_back(SharedPtr<MathCalculation>(
               new Division(settings.m_max_mult_div_value1, settings.m_max_mult_div_value2)));
         }
         if (settings.m_create_addition)
         {
            calculations.push_back(SharedPtr<MathCalculation>(new Addition(settings.m_max_add_sub_value)));
         }
         if (settings.m_create_multiplication)
         {
            calculations.push_back(SharedPtr<MathCalculation>(
               new Multiplication(settings.m_max_mult_div_value1, settings.m_max_mult_div_value2)));
         }
         if (settings.m_create_multiplication10)
         {
            calculations.push_back(SharedPtr<MathCalculation>(
               new Multiplication10(util::Min(settings.m_max_mult_div_value1, settings.m_max_mult_div_value2))));
         }
         if (settings.m_create_subtraction)
         {
            calculations.push_back(SharedPtr<MathCalculation>(new Subtraction(settings.m_max_add_sub_value)));
         }

         const std::string sep(";");
         for (uint32_t i=0; i< settings.m_num_calculations; i++)
         {
            uint32_t idx = rng->GetRandomNumber(0, uint32_t(calculations.size())-1);
            out << calculations[idx]->GetNextCalculationString(sep) << sep << "=" << sep << sep;
            if ((i+1)%4 == 0) out << endl;
         }
      }
   }
}

int main(int narg, const char** argv)
{
   tc::math_sheet::Settings settings;
   if (!tc::math_sheet::ParseCommandLine(narg, argv, settings))
   {
      return false;
   }

   tc::math_sheet::Create(settings);

   return 0;
}

