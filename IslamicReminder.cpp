
#include <iostream>
#include <string> 
#include <ctime>   // For time() to seed rand()
using namespace std;

// ---------------------- Reminder Base Class ----------------------
class Reminder {
public:
    virtual void show() {
        cout << "This is a general reminder." << endl;
    }
};

// ---------------------- Prayer Class ----------------------
class Prayer {
public:
    string name;
    string time;

    Prayer(string n, string t) {
        name = n;
        time = t;
    }
};

// ---------------------- Prayer Reminder Class ----------------------
class PrayerReminder : public Reminder {
private:
    Prayer* prayers[5];
    int currentHour24;
    int currentMinute;

public:
    PrayerReminder(int hour, int minute, string meridian) {
        if (hour == 12) hour = 0;
        if (meridian == "PM" || meridian == "pm") hour += 12;

        currentHour24 = hour;
        currentMinute = minute;

        prayers[0] = new Prayer("Fajr", "4:15 AM");
        prayers[1] = new Prayer("Zuhr", "1:30 PM");
        prayers[2] = new Prayer("Asr", "4:15 PM");
        prayers[3] = new Prayer("Maghrib", "6:45 PM");
        prayers[4] = new Prayer("Isha", "8:00 PM");
    }

    void show() override {
           int displayHour = currentHour24 % 12;
           if (displayHour == 0) displayHour = 12;
           cout << "\n🕒 Current Time: " << displayHour << ":"
               << (currentMinute < 10 ? "0" : "") << currentMinute << " ";
           cout << ((currentHour24 >= 12) ? "PM" : "AM") << endl;

        for (int i = 0; i < 5; i++) {
            string timeStr = prayers[i]->time;
            int hour = stoi(timeStr.substr(0, timeStr.find(":")));
            int minute = stoi(timeStr.substr(timeStr.find(":") + 1));
            string ampm = timeStr.substr(timeStr.size() - 2);

            if (ampm == "PM" && hour != 12) hour += 12;
            if (ampm == "AM" && hour == 12) hour = 0;

            if (currentHour24 < hour || (currentHour24 == hour && currentMinute < minute)) {
                if (i == 0) {
                    cout << "Previous Prayer: Isha (ended at 8:00 PM)\n";
                } else {
                    cout << "Current Prayer: " << prayers[i - 1]->name << endl;
                    cout << "Its ends"<< endl;
                }
                // 🌟 Variation messages
                int variation = rand() % 3;
                cout << "\n🌟 ";
                switch (variation) {
                    case 0: cout << "Get ready for your next prayer: "; break;
                    case 1: cout << "Upcoming prayer approaching: "; break;
                    case 2: cout << "Don't forget, next prayer is: "; break;
                }
                cout << prayers[i]->name << " at " << prayers[i]->time << endl;
                return;
            }
        }

        cout << "All prayers done. Next: Fajr at 4:15 AM\n";
    }

    void showTimetable() {
        cout << "\n🕌 Today's Prayer Times (Lahore):\n";
        cout << "-----------------------------\n";
        for (int i = 0; i < 5; i++) {
            cout << prayers[i]->name << " - " << prayers[i]->time << endl;
        }
    }
};

// ---------------------- Hadith Reminder ----------------------
class HadithReminder : public Reminder {
private:
    string hadiths[4];

public:
    HadithReminder() {
        hadiths[0] = "The best among you are those with best manners.";
        hadiths[1] = "Prayer is the key to success.";
        hadiths[2] = "Hearts find peace in remembering Allah.";
        hadiths[3] = "Speak good or remain silent.";
    }

    void show() override {
        cout << "\nChoose a Hadith (1-4): ";
        int i;
        cin >> i;
        if (i >= 1 && i <= 4)
            cout << "\nHadith: " << hadiths[i - 1] << endl;
        else
            cout << "Invalid selection." << endl;
    }
};

// ---------------------- Ayat Reminder ----------------------
class AyatReminder : public Reminder {
private:
    string ayats[10];
    string translations[10];

public:
    AyatReminder() {
        ayats[0] = "Indeed, Allah is with the patient.";
        translations[0] = "Beshak Allah Sabar karne walon k sath hai.";
        ayats[1] = "So remember Me; I will remember you.";
        translations[1] = "Mujhe yaad karo, Mein tumhe yaad karunga.";
        ayats[2] = "And He found you lost and guided [you].";
        translations[2] = "Usne tumhe gumrah paya aur hidayat di.";
        ayats[3] = "Indeed, with hardship comes ease.";
        translations[3] = "Har mushkil k sath asani hai.";
        ayats[4] = "Verily, in the remembrance of Allah do hearts find rest.";
        translations[4] = "Allah k zikr mein dil ka sukoon hai.";
        ayats[5] = "Your Lord has not forsaken you.";
        translations[5] = "Tumhara Rab tumhe chor nahi gaya.";
        ayats[6] = "Allah does not burden a soul beyond that it can bear.";
        translations[6] = "Allah kisi par uski taqat se zyada bojh nahi dalta.";
        ayats[7] = "And seek help through patience and prayer.";
        translations[7] = "Sabar aur namaz se madad lo.";
        ayats[8] = "He is with you wherever you are.";
        translations[8] = "Woh har jagah tumhare sath hai.";
        ayats[9] = "Do not despair of the mercy of Allah.";
        translations[9] = "Allah ki rehmat se mayoos na ho.";
    }

    void show() override {
        cout << "\nChoose Ayat (1–10): ";
        int i;
        cin >> i;
        if (i >= 1 && i <= 10) {
            cout << "\nAyat: " << ayats[i - 1] << endl;
            cout << "Tarjuma: " << translations[i - 1] << endl;
        } else {
            cout << "Invalid selection." << endl;
        }
    }
};

// ---------------------- Qibla Direction ----------------------
class QiblaDirection : public Reminder {
public:
    void show() override {
        cout << "\nSelect your city:\n";
        cout << "1. Lahore\n2. Islamabad\n3. Rawalpindi\n4. Karachi\n5. Quetta\n6. Multan\n7. Faisalabad\n";
        int choice;
        cin >> choice;

        cout << "\n🧭 Qibla Direction:\n";
        switch (choice) {
            case 1: cout << "Lahore: 251.88° WSW towards Mecca\n"; break;
            case 2: cout << "Islamabad: 243.10° WSW towards Mecca\n"; break;
            case 3: cout << "Rawalpindi: 243.25° WSW towards Mecca\n"; break;
            case 4: cout << "Karachi: 259.11° WSW towards Mecca\n"; break;
            case 5: cout << "Quetta: 267.58° WSW towards Mecca\n"; break;
            case 6: cout << "Multan: 253.00° WSW towards Mecca\n"; break;
            case 7: cout << "Faisalabad: 251.20° WSW towards Mecca\n"; break;
            default: cout << "Invalid selection.\n";
        }
    }
};

// ---------------------- Hijri Calendar ----------------------
class HijriDate : public Reminder {
public:
    void show() override {
        int gDay, gMonth, gYear;
        cout << "\nEnter today's Gregorian Date (DD MM YYYY): ";
        cin >> gDay >> gMonth >> gYear;

        int jd = (1461 * (gYear + 4800 + (gMonth - 14) / 12)) / 4 +
                 (367 * (gMonth - 2 - 12 * ((gMonth - 14) / 12))) / 12 -
                 (3 * ((gYear + 4900 + (gMonth - 14) / 12) / 100)) / 4 +
                 gDay - 32075;

        int l = jd - 1948440 + 10632;
        int n = (l - 1) / 10631;
        l = l - 10631 * n + 354;
        int j = ((10985 - l) / 5316) * ((50 * l) / 17719) + (l / 5670) * ((43 * l) / 15238);
        l = l - ((30 - j) / 15) * ((17719 * j) / 50) - (j / 16) * ((15238 * j) / 43) + 29;
        int m = (24 * l) / 709;
        int d = l - (709 * m) / 24;
        int y = 30 * n + j - 30;

        string months[] = {"", "Muharram", "Safar", "Rabi al-Awwal", "Rabi al-Thani", "Jumada al-Awwal", "Jumada al-Thani",
                           "Rajab", "Sha'ban", "Ramadan", "Shawwal", "Dhul-Qadah", "Dhul-Hijjah"};

        cout << "\n📅 Hijri Date Today: " << d << " " << months[m] << " " << y << " AH\n";
    }
};

// ---------------------- Dua Reminder ----------------------
class DuaReminder : public Reminder {
private:
    string duas[5] = {
        "O Allah, forgive me and have mercy on me.",
        "O Allah, help me remember You and be grateful to You.",
        "O Turner of the hearts, keep my heart firm upon Your religion.",
        "O Allah, I ask You for beneficial knowledge, pure sustenance, and accepted deeds.",
        "O Allah, guide me among those whom You have guided."
    };

public:
    void show() override {
        int choice;
        cout << "\nChoose Dua (1–5): ";
        cin >> choice;
        if (choice >= 1 && choice <= 5)
            cout << "\n🤲 Dua: " << duas[choice - 1] << endl;
        else
            cout << "Invalid choice.\n";
    }
};

// ---------------------- Zakat Calculator ----------------------
class ZakatCalculator : public Reminder {
public:
    void show() override {
        float wealth;
        cout << "\nEnter total savings (gold, cash, etc.): Rs. ";
        cin >> wealth;

        if (wealth >= 93000) {
            float zakat = wealth * 0.025;
            cout << "Your Zakat is: Rs. " << zakat << endl;
        } else {
            cout << "You are not eligible for Zakat (below Nisab).\n";
        }
    }
};

// ---------------------- Tasbeeh Counter ----------------------
class TasbeehCounter : public Reminder {
public:
    void show() override {
        int count = 0;
        char choice;
        cout << "\nPress 'y' to count Tasbeeh, 'q' to quit.\n";
        while (true) {
            cout << "Count: " << count << " ➤ ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                count++;
            } else if (choice == 'q' || choice == 'Q') {
                break;
            } else {
                cout << "Invalid input. Use 'y' to count or 'q' to quit.\n";
            }
        }
        cout << "Total Tasbeeh Count: " << count << endl;
    }
};

// ---------------------- Main Function ----------------------
int main() {
    cout << "\n========================================\n";
    cout << "     🌙 ISLAMIC REMINDER SYSTEM 🌙\n";
    cout << "========================================\n";

    int hour, minute;
    char colon;
    string meridian;

    cout << "Enter current time (e.g. 12:30): ";
    cin >> hour >> colon >> minute;
    cout << "Enter AM or PM: ";
    cin >> meridian;

    // Seed random variations
    srand((unsigned)time(nullptr));

    int choice;
    while (true) {
        cout << "\n===== Islamic Reminder Menu =====\n";
        cout << "1. Prayer Reminder\n";
        cout << "2. Prayer Timetable View\n";
        cout << "3. Hadith of the Day\n";
        cout << "4. Ayat of the Day\n";
        cout << "5. Dua of the Day\n";
        cout << "6. Qibla Direction\n";
        cout << "7. Hijri Date\n";
        cout << "8. Zakat Calculator\n";
        cout << "9. Tasbeeh Counter\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        Reminder* r = nullptr;

        switch (choice) {
            case 1: r = new PrayerReminder(hour, minute, meridian); break;
            case 2: {
                PrayerReminder p(hour, minute, meridian);
                p.showTimetable();
                continue;
            }
            case 3: r = new HadithReminder(); break;
            case 4: r = new AyatReminder(); break;
            case 5: r = new DuaReminder(); break;
            case 6: r = new QiblaDirection(); break;
            case 7: r = new HijriDate(); break;
            case 8: r = new ZakatCalculator(); break;
            case 9: r = new TasbeehCounter(); break;
            case 0: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice.\n"; continue;
        }

        if (r != nullptr) {
            r->show();
            delete r;
        }
    }

    return 0;
}